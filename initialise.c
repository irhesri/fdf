#include "fdf.h"

static t_point	**list_to_array(t_line *line, int *size)
{
	int		i;
	int		j;
	char	**p;
	t_point	**map;

	map = (t_point **) malloc(sizeof(t_point *) * (size[0] + 1));
	(!map) && error_case();
	i = 0;
	while (line)
	{
		map[i] = (t_point *) malloc(sizeof(t_point) * size[1]);
		p = line->points;
		j = 0;
		while (p[j])
		{
			(&map[i][j]) -> x = (j + 1) * 30;
			(&map[i][j]) -> y = (i + 1) * 30;
			(&map[i][j]) -> z = my_atoi(p[j], &map[i][j]);
			// int x = (&map[i][j]) -> x;
			// (&map[i][j]) -> x = x - (&map[i][j]) -> y;
			// (&map[i][j]) -> y = (x + (&map[i][j]) -> y) / 2;

			// (&map[i][j]) -> x = (&map[i][j]) -> x / sin(0.7);
			// (&map[i][j]) -> x = (j - i) * 30 * cos(0.7);
			// (&map[i][j]) -> y = (i + j + 2) * 30 * sin(0.7) - (&map[i][j]) -> z;
			// printf("%d - %d\n", (&map[i][j]) -> x, (&map[i][j]) -> y);
			if ((&map[i][j]) -> z > 0)
			{
				(&map[i][j]) -> x /= (&map[i][j]) -> z;
				(&map[i][j]) -> y /= (&map[i][j]) -> z;
			}
			printf("%d - %d\n", (&map[i][j]) -> x, (&map[i][j]) -> y);
			j++;
		}
		line = line->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

t_point	**get_map(char *file, int *size)
{
	int		fd;
	int		len;
	char	*str;
	t_line	*lines;

	fd = open(file, O_RDONLY);
	(fd < 0) && error_case();
	str = get_next_line(fd);
	(!str || !*str) && error_case();
	size[0] = 0;
	size[1] = 0;
	lines = NULL;
	while (str)
	{
		my_push_back(&lines, ft_split(str, ' ', &len));
		if (!size[1])
			size[1] = len;
		(size[1] != len) && error_case();
		free(str);
		str = get_next_line(fd);
		size[0]++;
	}
	return(list_to_array(lines, size));
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