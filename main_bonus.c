/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:14:41 by irhesri           #+#    #+#             */
/*   Updated: 2023/05/15 15:35:38 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	get_window_size(t_window *win, int key)
{
	int	width;
	int	length;

	if (win->x[0] >= 0)
		length = win->x[0] - win->n[0];
	else
		length = abs(win->n[0]) - abs(win->x[0]);
	if (win->x[1] >= 0)
		width = win->x[1] - win->n[1];
	else
		width = abs(win->n[1]) - abs(win->x[1]);
	if (key > 0 && (length > 9000 || width > 9000))
	{
		win->zoom -= 0.2 * ((key == PLUS) - (key == MINUS && win->zoom > 0));
		win->teta -= 0.1 * ((key == A) - (key == D));
		win->z -= 1 * ((key == W) - (key == S));
		win->p = (key == P) * !win->p + (key != P) * win->p;
		return (0);
	}
	new_image(win, width + 10, length + 10);
	return (1);
}

static int	my_close(t_window *win)
{
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
}

int	key_hook(int key, t_window *win)
{
	(key == ESC) && my_close(win);
	if ((key == UP) || (key == DOWN) || (key == RIGHT) || (key == LEFT))
	{
		win->trans[1] += 20 * ((key == RIGHT) - (key == LEFT)) * win->zoom;
		win->trans[0] += 20 * ((key == DOWN) - (key == UP)) * win->zoom;
		mlx_clear_window(win->mlx, win->win);
		mlx_put_image_to_window (win->mlx, win->win, win->image->img,
			win->trans[1], win->trans[0]);
		return (1);
	}
	win->zoom += 0.2 * ((key == PLUS) - (key == MINUS && win->zoom > 0));
	win->teta += 0.1 * ((key == A) - (key == D));
	win->z += 1 * ((key == W) - (key == S));
	win->p = (key == P) * !win->p + (key != P) * win->p;
	list_to_array(win->lines, win, win->map, 0);
	if (!get_window_size(win, key))
		list_to_array(win->lines, win, win->map, 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_window	*window;

	check_args(av[1], ac);
	window = (t_window *) malloc(sizeof(t_window));
	!(window) && error_case(0);
	window->image = (t_image *) malloc(sizeof(t_image));
	!(window->image) && error_case(0);
	window->image->img = NULL;
	window->map_size[0] = 0;
	window->trans[0] = 0;
	window->trans[1] = 0;
	window->teta = 0.4;
	window->zoom = 1;
	window->z = 2;
	window->p = 0;
	window->color = 0xFFFFFF;
	window->map = get_map(av[1], window->map_size, window);
	window->mlx = mlx_init();
	(!window->mlx) && error_case(6);
	window->win = mlx_new_window(window->mlx, 1910, 1250, "fdf"); // you can change the size
	(!window->win) && error_case(6);
	get_window_size(window, -1);
	mlx_hook(window->win, 2, 1L << 0, key_hook, window);
	mlx_hook(window->win, 17, 0, my_close, window);
	mlx_loop(window->mlx);
}
