#include "fdf.h"

void    my_push_back(t_line **list, char **data)
{
    t_line *lst;
    t_line *new;

    (!data || !*data) && error_case();
    new = malloc(sizeof(t_line));
    (new -> points) = data;
    new -> next = NULL; 
    if (!*list)
    {
        *list = new;
        return ;
    }
    lst = *list;
    while (lst -> next)
        lst = lst -> next;
    lst -> next = new;
}

int	error_case(void)
{
	ft_putstr_fd("ERROR", 2);
	exit (0);
	return (0);
}