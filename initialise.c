#include "fdf.h"

static void	list_to_array(t_line *line, int *size, t_window *win, t_point **map)
{
	int	i;
	int	j;

	i = -1;
	while (line)
	{
		map[++i] = (t_point *) malloc(sizeof(t_point) * size[1]);
		j = -1;
		while (++j < win->map_size[1])
		{
			(&map[i][j])->x = (j - i) * 20;
			(&map[i][j])->z = my_atoi(line->points[j], &map[i][j]) * 15;
			(&map[i][j])->y = (j + i) * 10 - (&map[i][j])->z;
			if ((i == 0 && j == 0) || (win->min[0] > (&map[i][j])->y))
				win->min[0] = (&map[i][j])->y;
			if ((i == 0 && j == 0) || (win->min[1] > (&map[i][j])->x))
				win->min[1] = (&map[i][j])->x;
			if ((i == 0 && j == 0) || (win->max[0] < (&map[i][j])->y))
				win->max[0] = (&map[i][j])->y;
			if ((i == 0 && j == 0) || (win->max[1] < (&map[i][j])->x))
				win->max[1] = (&map[i][j])->x;
		}
		line = line->next;
	}
	map[++i] = NULL;
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
	size[0] = 0;
	lines = NULL;
	while (str)
	{
		my_push_back(&lines, ft_split(str, ' ', &len));
		if (!size[0]++)
			size[1] = len;
		(size[1] != len) && error_case(4);
		free(str);
		str = get_next_line(fd);
	}
	map = (t_point **) malloc(sizeof(t_point *) * (size[0] + 1));
	(!map) && error_case(0);
	list_to_array(lines, size, win, map);
	return (map);
}
