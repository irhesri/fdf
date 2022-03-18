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

static void	get_window(t_window *win, t_image *img)
{
	int		width;
	int		height;
	char	*a;

	if (win->max[0] >= 0)
		height = win->max[0] - win->min[0] + 20;
	else
		height = abs(win->min[0]) - abs(win->max[0]) + 20;
	if (win->max[1] >= 0)
		width = win->max[1] - win->min[1] + 20;
	else
		width = abs(win->min[1]) - abs(win->max[1]) + 20;
	win->win = mlx_new_window(win->mlx, width, height, "fdf");
	img->img = mlx_new_image(win->mlx, width, height);
	a = mlx_get_data_addr(img->img, &(img->bit), &(img->size), &(img->endian));
	img->address = a;
	win->image = img;
}

static int	key_hook(int keycode, t_window *win)
{
	if (keycode == 53)
	{	
		mlx_destroy_window(win->mlx, win->win);
		exit(0);
	}
	return (1);
}

static int	my_close(t_window *win)
{
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
	return (1);
}

int	main(int ac, char **av)
{
	t_window	*window;
	t_image		*img;
	int			size;

	size = ft_strlen(av[1]) - 4;
	if (ac != 2 || av[1][size++] != '.' || av[1][size++] != 'f'
		|| av[1][size++] != 'd' || av[1][size] != 'f')
		error_case(5);
	if (ac != 2)
		error_case(5);
	window = (t_window *) malloc(sizeof(t_window));
	img = (t_image *) malloc(sizeof(t_image));
	window->map_size[0] = 0;
	window->color = 0xFFFFFF;
	window->map = get_map(av[1], window->map_size, window);
	window->mlx = mlx_init();
	get_window(window, img);
	draw_map(window->map, window);
	mlx_put_image_to_window (window->mlx, window->win, img->img, 0, 0);
	mlx_hook(window->win, 2, 1L << 0, key_hook, window);
	mlx_hook(window->win, 17, 0, my_close, window);
	mlx_loop(window->mlx);
}
