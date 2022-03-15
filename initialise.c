#include "fdf.h"

static void	my_push_back(t_line **list, char **data)
{
	t_line	*lst;
	t_line	*new;

	(!data || !*data) && error_case(4);
	new = malloc(sizeof(t_line));
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

void	min_max(t_window *win, int n, short k, short b)
{
	if (b || win->min[k] > n)
		win->min[k] = n;
	if (b || win->max[k] < n)
		win->max[k] = n;
}

void	list_to_array(t_line *line, int *size, t_window *win, t_point **map)
{
	static int	width;
	int	i;
	int	j;

	if (!width)
	{
		i = 1000 / win->map_size[1];
		j = 500 / win->map_size[0];
		width = i * (i <= j) + j * (i > j);
		width = width * (width <= 20) + 20 * (width > 20);
	}

	i = -1;
	while (line)
	{
		map[++i] = (t_point *) malloc(sizeof(t_point) * size[1]);
		j = -1;
		while (++j < win->map_size[1])
		{
			(&map[i][j])->x = (j - i) * cos(win->teta) * width * win->zoom;
			(&map[i][j])->z = my_atoi(line->points[j], &map[i][j]) * win->z * win->zoom;
			(&map[i][j])->y = (j + i) * sin(win->teta) * width * win->zoom;
			(&map[i][j])->y -= (&map[i][j])->z;

			min_max(win, (&map[i][j])->y, 0, (i == 0 && j == 0));
			min_max(win, (&map[i][j])->x, 1, (i == 0 && j == 0));
		}
		line = line->next;
	}
	map[++i] = NULL;
}

static void	free_function(t_line *lines)
{
	t_line	*l;
	int		i;

	while (lines)
	{
		l = lines->next;
		i = 0;
		while (lines->points[i])
			free(lines->points[i++]);
		free(lines->points);
		free(lines);
		lines = l;
	}
}

t_point	**get_map(char *file, int *size, t_window *win)
{
	int		fd;
	int		len;
	char	*str;
	t_line	*lines;
	t_point	**map;

	fd = open(file, O_RDONLY);
	(fd < 0) && error_case(1);
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
	// map = (t_point **) malloc(sizeof(t_point *) * (size[0] + 1));
	// (!map) && error_case(0);
	// int i = 0;
	// while (i < win->map_size[0])
	// {
	// 	map[i++] = malloc(4);
	// }
	
	// list_to_array(lines, size, win, map);
	win->lines = lines;
	// free_function(lines);
	return (map);
}
