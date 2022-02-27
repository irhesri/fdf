#include "fdf.h"

int main(int ac, char **av)
{
    int     fd;
    int     i;
    char    *str;
    char    **map;

    fd = open(av[1], fd, O_RDONLY);
    // if (fd < 0)          // error accessing file
    //     error
    str = get_next_line(fd);
    // if (!str || !*str)    //empty file
        // .
    map = NULL;
    while (str)
    {
        free (map);
        map = ft_split(str, ' ', &i);
        i = 0;
        while (map[i])
        {
            printf("%s  ", map[i++]);
        }
        printf("\n");
        free (str);
        str = get_next_line(fd);
    }
}