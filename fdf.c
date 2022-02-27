#include "fdf.h"

void	error_case()
{
	ft_putstr_fd("Error\n", 2);
	exit (0);
}

char	**get_map(char *file, int *size)
{
	int		fd;
	int		i;
	char	**str;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_case();		//can't open the file
	i = 0;
	str[i] = get_next_line(fd);
	if (!str[i])
		error_case();		//empty file
	while (str[i++])
		str[i] = get_next_line(fd);
	size[0] = i - 1;
	return (str);
}


int	**to_int(char **str, int *size)
{
	int		i;
	int		j;
	int		len;
	int		**map;
	char	**line;
	
	map = (int **) malloc(sizeof(int *) * size[0]);
	if (!map)
		error_case();	//allocation problem
	len = 0;
	i = 0;
	while (str[i])
	{
		line = ft_split(str, ' ', size + 1);
		if (!len)
			size[1] = len;
		else if (len != size[1])
			error_case();	//wrong map
		map[i] = (int *) malloc(sizeof(int) * len);
		if (!map[i])
			error_case();	//allocation problem
		j = 0;
		while (j < size[1])
		{
			map[i][j] = my_atoi(line[j]);
			j++;
		}
		free(line);
		i++;
	}
	free(str);
}

void	check_extension(char *file)
{
	int len;
	len = 14;
	len = ft_strlen(file);
	if (len < 5)
		error_case();
	if (!my_strcmp(file + len - 4, ".fdf"))
		return ;
	error_case();			// wrong extension
}

int main(int ac, char **av)
{
    char	*file;
    int		**map;
	int		size[2];

    if (ac != 2)
        error_case();		//wrong number of arguments
	file = *(av + 1);
	check_extension(file);
	map = to_int(get_map(file, size), size);
	
}
