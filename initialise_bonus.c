/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:13:59 by irhesri           #+#    #+#             */
/*   Updated: 2022/03/17 21:14:01 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	my_push_back(t_line **list, char **data)
{
	t_line	*lst;
	t_line	*new;

	new = malloc (sizeof (t_line));
	new->points = data;
	new->next = NULL;
	if (!*list)
	{
		*list = new;
		return ;
	}
	lst = *list;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}

static void	min_max(t_window *win, int n, short k, short b)
{
	if (b || win->n[k] > n)
		win->n[k] = n;
	if (b || win->x[k] < n)
		win->x[k] = n;
}

static int	get_width(t_window *win, int *width)
{
	int	i;
	int	j;

	i = 1000 / win->map_size[1];
	j = 500 / win->map_size[0];
	(*width) = i * (i <= j) + j * (i > j);
	(*width) = (*width) * ((*width) <= 25) + 25 * ((*width) > 25);
	if (!(*width))
		(*width) = 1;
	return (1);
}

void	list_to_array(t_line *line, t_window *w, t_point **map, short b)
{
	static int	len;
	int			i;
	int			j;

	(!len) && get_width(w, &len);
	i = -1;
	while (++i < w->map_size[0])
	{
		if (b)
			map[i] = malloc(sizeof(t_point) * (w->map_size[1] + 1));
		(!map[i]) && error_case(0);
		j = -1;
		while (++j < w->map_size[1])
		{
			(&map[i][j])->z = my_atoi(line->points[j], &map[i][j]) * w->zoom;
			(&map[i][j])->x = ((j - i) * cos(w->teta) * !w->p + j * w->p)
				* len * w->zoom;
			(&map[i][j])->y = ((j + i) * sin(w->teta) * !w->p + i * w->p)
				* len * w->zoom - (&map[i][j])->z * w->z * !w->p;
			min_max(w, (&map[i][j])->y, 0, (i == 0 && j == 0));
			min_max(w, (&map[i][j])->x, 1, (i == 0 && j == 0));
		}
		line = line->next;
	}
	map[i] = NULL;
}

t_point	**get_map(char *file, int *size, t_window *win)
{
	int		fd;
	int		len;
	char	*str;
	t_line	*lines;
	t_point	**map;

	fd = open(file, O_RDONLY);
	(fd < 0) && error_case(2);
	str = get_next_line(fd);
	(!str || !*str) && error_case(3);
	lines = NULL;
	while (str)
	{
		my_push_back(&lines, ft_split(str, ' ', &len));
		if (!size[0]++)
			size[1] = len;
		(size[1] != len || !*str) && error_case(4);
		free(str);
		str = get_next_line(fd);
	}
	map = (t_point **) malloc(sizeof(t_point *) * (win->map_size[0] + 1));
	(!map) && error_case(0);
	list_to_array(lines, win, map, 1);
	win->lines = lines;
	return (map);
}
