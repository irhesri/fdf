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

#include "fdf_bonus.h"

int	get_window_size(t_window *win, int keycode)
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
	if (keycode > 0 && (length > 9000 || width > 9000))
	{
		win->zoom -= 0.2 * ((keycode == 69) - (keycode == 78 && win->zoom > 0));
		win->teta -= 0.1 * ((keycode == 0) - (keycode == 2));
		win->z -= 1 * ((keycode == 13) - (keycode == 1));
		win->p = (keycode == 35) * !win->p + (keycode != 35) * win->p;
		return (0);
	}
	new_image(win, width + 10, length + 10);
	return (1);
}

int	my_close(t_window *win)
{
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
	return (1);
}

int	key_hook(int keycode, t_window *win)
{
	(keycode == 53) && my_close(win);
	if (122 < keycode && keycode < 127)
	{
		win->trans[1] += 20 * ((keycode == 124) - (keycode == 123)) * win->zoom;
		win->trans[0] += 20 * ((keycode == 125) - (keycode == 126)) * win->zoom;
		mlx_clear_window(win->mlx, win->win);
		mlx_put_image_to_window (win->mlx, win->win, win->image->img,
			win->trans[1], win->trans[0]);
		return (1);
	}
	win->zoom += 0.2 * ((keycode == 69) - (keycode == 78 && win->zoom > 0));
	win->teta += 0.1 * ((keycode == 0) - (keycode == 2));
	win->z += 1 * ((keycode == 13) - (keycode == 1));
	win->p = (keycode == 35) * !win->p + (keycode != 35) * win->p;
	list_to_array(win->lines, win, win->map, 0);
	if (!get_window_size(win, keycode))
		list_to_array(win->lines, win, win->map, 0);
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

	if (wrong_args(av[1], ac))
		error_case(5);
	window = (t_window *) malloc(sizeof(t_window));
	!(window) && error_case(0);
	window->image = NULL;
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
	window->win = mlx_new_window(window->mlx, 2500, 1350, "fdf");
	(!window->win) && error_case(6);
	get_window_size(window, -1);
	mlx_hook(window->win, 2, 1L << 0, key_hook, window);
	mlx_hook(window->win, 17, 0, my_close, window);
	mlx_loop(window->mlx);
}
