#include "fdf.h"

static t_point	**list_to_array(t_line *line, int *size, t_window *win)
{
	int		i;
	int		j;
	char	**p;
	t_point	**map;
	t_line *t;

	t = line;
	map = (t_point **) malloc(sizeof(t_point *) * (size[0] + 1));
	(!map) && error_case(0);
	i = 0;
	while (line)
	{
		map[i] = (t_point *) malloc(sizeof(t_point) * (size[1] + 1));
		p = line->points;
		j = -1;
		while (++j < win->map_size[1])
		{
			//	x = x - y;
			//	y = (x + y) / 2;
			(&map[i][j]) -> x = j * 20;
			(&map[i][j]) -> y = i * 20;
			(&map[i][j]) -> z = my_atoi(p[j], &map[i][j]) * 15;
			int x = (&map[i][j]) -> x;
			int y = (&map[i][j]) -> y;
			int z = (&map[i][j]) -> z;





			// y = (&map[i][j]) -> y;
			// (&map[i][j]) -> x = cos(3.14) * x + sin(3.14) * z;
			// (&map[i][j]) -> z = 0 - sin(3.14) * x + cos(3.14) * z;

			// RX:
			// (&map[i][j]) -> x = x;
			// (&map[i][j]) -> y =	cos(-0.4) * y - sin(-0.4) * z;
			// (&map[i][j]) -> z = sin(-0.4) * y + cos(-0.4) * z;

			// (&map[i][j]) -> x =  - y;
			// (&map[i][j]) -> y -= (x + y) / 2  - (&map[i][j]) -> z;
			// x = (&map[i][j]) -> x;
			// if (z > 0)

			(&map[i][j]) -> x = x - y;
			(&map[i][j]) -> y = (x + y) / 2;
			(&map[i][j]) -> y -= (&map[i][j]) -> z;

			x = (&map[i][j]) -> x;
			y = (&map[i][j]) -> y;

			// (&map[i][j]) -> x = cos(-1.5) * x - sin(-1.5) * y;
			// (&map[i][j]) -> y = sin(-1.5) * x + cos(-1.5) * y;
		
			// (&map[i][j]) -> x = cos(-1) * x - sin(-1) * y;
			// (&map[i][j]) -> y = sin(-1) * x + cos(-1) * y;


			if ((i == 0 && j == 0) || (win->min[0] > (&map[i][j]) -> y))
				win->min[0] = (&map[i][j]) -> y;
			if ((i == 0 && j == 0) || (win->min[1] > (&map[i][j]) -> x))
				win->min[1] = (&map[i][j]) -> x;
			if ((i == 0 && j == 0) || (win->max[0] < (&map[i][j]) -> y))
				win->max[0] = (&map[i][j]) -> y;
			if ((i == 0 && j == 0) || (win->max[1] < (&map[i][j]) -> x))
				win->max[1] = (&map[i][j]) -> x;
			// if ((&map[i][j]) -> z > 0)
			// {
			// 	(&map[i][j]) -> x /= (&map[i][j]) -> z;
			// 	(&map[i][j]) -> y /= (&map[i][j]) -> z;
			// }
		}
		// map[i][j] = NULL;
		line = line->next;
		i++;
	}
	map[i] = NULL;
	t_line	*s;
	while (t)
	{
		s = t->next;
		p = t -> points;
		j = -1;
		while (++j < win->map_size[1])
			free (p[j]);
		free(p);
		free(t);
		t = s;
	}
	
	return (map);
}

t_point	**get_map(char *file, int *size, t_window *win)
{
	int		fd;
	int		len;
	char	*str;
	t_line	*lines;

	fd = open(file, O_RDONLY);
	(fd < 0) && error_case(1);
	str = get_next_line(fd);
	(!str || !*str) && error_case(3);
	size[0] = 0;
	size[1] = 0;
	lines = NULL;
	while (str)
	{
		my_push_back(&lines, ft_split(str, ' ', &len));
		if (!size[1])
			size[1] = len;
		(size[1] != len) && error_case(4);
		free(str);
		str = get_next_line(fd);
		size[0]++;
	}
	return(list_to_array(lines, size, win));
}


char	*get_color(void)
{
 	static int	i;
	static char	**colors;

	if (!colors)
	{
		colors = malloc(sizeof(char *) * 10);
		while (i < 10)
			colors[i++] = malloc(sizeof(char) * 9);	
		colors[0] = "0xffffff";
		colors[1] = "0x87cefa";
		colors[2] = "0xffff";
		colors[3] = "0xf08080";
		colors[4] = "0xffa500";
		colors[5] = "0xd8bfd8";
		colors[6] = "0x7cfc00";
		colors[7] = "0xffb6c1";
		colors[8] = "0xffd700";
		colors[9] = "0x8470ff";
		i = -1;
	}
	i++;
	if (i > 9)
		i = 0;
	return (colors[i]);
}