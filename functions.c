#include "fdf.h"

void    my_push_back(t_line **list, char **data)
{
    t_line *lst;
    t_line *new;

    // (!data || !*data) && error_case();
    new = malloc(sizeof(t_line));
    (new->points) = data;
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

int	error_case(short n)
{
	if (n == 0)
		ft_putstr_fd("ALLOCATION ERROR", 2);
	else if (n == 1)
		ft_putstr_fd("Z SHOULD BE A NUMBER", 2);
	else if (n == 2)
		ft_putstr_fd("CAN'T OPEN THE FILE", 2);
	else if (n == 3)
		ft_putstr_fd("EMPTY FILE", 2);
	else if (n == 4)
		ft_putstr_fd("Found wrong line length. Exiting.", 2);
	else if (n == 5)
		ft_putstr_fd("WRONG ARGUMENTS", 2);
	else if (n == 6)
		ft_putstr_fd("WRONG MAP", 2);
	ft_putstr_fd("\n", 2);
	exit (0);
	return (0);
}