/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:14:41 by irhesri           #+#    #+#             */
/*   Updated: 2022/03/17 21:14:44 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_window_size(t_window *win, int *width, int *length)
{
	if (win->x[0] >= 0)
		(*length) = win->x[0] - win->n[0] + 20;
	else
		(*length) = abs(win->n[0]) - abs(win->x[0]) + 20;
	if (win->x[1] >= 0)
		(*width) = win->x[1] - win->n[1] + 20;
	else
		(*width) = abs(win->n[1]) - abs(win->x[1]) + 20;
	return (0);
}

static int	my_close(t_window *win)
{
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
	return (1);
}

static int	key_hook(int keycode, t_window *win)
{
	(keycode == 53) && my_close(win);
	return (1);
}

static int	wrong_args(char *str, int ac)
{
	int			size;

	size = ft_strlen(str) - 4;
	if (ac != 2 || size < 0 || str[size++] != '.' || str[size++] != 'f'
		|| str[size++] != 'd' || str[size] != 'f')
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_window	*window;
	int			width;
	int			length;

	if (wrong_args(av[1], ac))
		error_case(5);
	window = (t_window *) malloc(sizeof(t_window));
	!(window) && error_case(0);
	window->image = NULL;
	window->map_size[0] = 0;
	window->map = get_map(av[1], window->map_size, window);
	get_window_size(window, &width, &length);
	window->mlx = mlx_init();
	(!window->mlx) && error_case(6);
	window->win = mlx_new_window(window->mlx, width, length, "fdf");
	(!window->win) && error_case(6);
	new_image(window, width, length);
	mlx_hook(window->win, 2, 1L << 0, key_hook, window);
	mlx_hook(window->win, 17, 0, my_close, window);
	mlx_loop(window->mlx);
}
