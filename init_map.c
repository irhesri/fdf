#include "fdf.h"

t_line	*initialise(char **data)
{
	t_line	*lst;

	lst = (t_line *) malloc(sizeof(t_line));
	if (!lst)
		return (NULL);
	lst->line = data;
	lst->next = NULL;
	return (lst);
}

void	my_push_back(t_line **list, t_line *new)
{
	t_line	*lst;

	if (!new)
		return ;
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

void    init_line(t_line  **map, char *str)
{
    t_line      *element;
    static int  size;
    int         len;

    if (!size)
        element = initialise(ft_split(str, ' ', &size));
    else
    {
        element = initialise(ft_split(str, ' ', &len));
        // if (len != size)
        //     error
    }
    my_push_back(map, element);
}

t_line  *get_map(char *file)
{
    int     fd;
    int     i;
    char    *str;
    t_line  *map;

    fd = open(file, fd, O_RDONLY);
    // if (fd < 0)          // error accessing file
    //     error
    str = get_next_line(fd);
    // if (!str || !*str)    //empty file
        // .
    map = NULL;
    while (str)
    {
        init_line (&map, str);
        free (str);
        str = get_next_line(fd);
    }
    return (map);
}