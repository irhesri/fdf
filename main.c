#include "fdf.h"

t_point	**list_to_array(t_line *line, int *size)
{
	int		i;
	int		j;
	char	**p;
	t_point	**map;

	map = (t_point **) malloc(sizeof(t_point *) * (size[1] + 1));
	(!map) && error_case();
	i = 0;
	while (line)
	{
		map[i] = (t_point *) malloc(sizeof(t_point) * (size[0] + 1));
		p = line->points;
		j = 0;
		while (p[j])
		{
			(&map[i][j]) -> x = j;
			(&map[i][j]) -> y = i;
			(&map[i][j]) -> z = my_atoi(p[j]);
			j++;
		}
		line = line->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}


t_point	**get_map(char *file)
{
	int		fd;
	int		size[3];
	char	*str;
	t_line	*lines;

	fd = open(file, O_RDONLY);
	(fd < 0) && error_case();
	str = get_next_line(fd);
	(!str || !*str) && error_case();
	size[1] = 0;
	size[2] = 0;
	lines = NULL;
	while (str)
	{
		my_push_back(&lines, ft_split(str, ' ', size));
		if (!size[1])
			size[1] = size[0];
		(size[1] != size[0]) && error_case();
		free(str);
		str = get_next_line(fd);
		size[2]++;
	}
	return(list_to_array(lines, size + 1));
}

int	main(int ac, char **av)
{
	t_point **map;
	int i = 0,j = 0;
	int fd = open(av[1], O_RDONLY);
	if (ac != 2)
		error_case();
	map = get_map(av[1]);
	while (map[i])
	{
		j = 0;
		while (j < 11)
		{
			printf("%d  ", (&map[i][j]) -> z);
			j++;
		}
		i++;
		printf("\n");
	}
	
}