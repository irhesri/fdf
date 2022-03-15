#include "fdf.h"
void	new_image(t_window *window);

int		out_of_window(t_window *win)
{
	int	width;
	int	length;

	if (win->max[0] >= 0)
		length = win->max[0] - win->min[0] + win->trans[0];
	else
		length = abs(win->max[0]) + abs(win->min[0]) + win->trans[0];
	if (win->max[1] >= 0)
		width = win->max[1] - win->min[1] + win->trans[1];
	else
		width = abs(win->max[1]) + abs(win->min[1]) + win->trans[1];
	if (length > 1500 || width > 2500)
		return (1);
	return (0);
}

int	key_hook(int keycode, t_window *win)
{
	// printf("%d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(win->mlx, win->win);
		exit (0);
	}
	else if (keycode == 124)
	{
		win->trans[1] += 15;
		if (!out_of_window(win))
			new_image(win);
		else
			win->trans[1] -= 15;
	}
	else if (keycode == 123)
	{
		if (win->trans[1] > 15) 
		{
			win->trans[1] -= 15;
			if (!out_of_window(win))
				new_image(win);
			else
				win->trans[1] += 15;
		}
	}
	else if (keycode == 126)
	{
		if (win->trans[0] > 15) 
		{	
			win->trans[0] -= 15;
			if (!out_of_window(win))
				new_image(win);
			else
				win->trans[0] += 15;
		}
	}
	else if (keycode == 125)
	{
		win->trans[0] += 15;
		if (!out_of_window(win))
			new_image(win);
		else
			win->trans[0] -= 15;
	}
	else if (keycode == 69)
	{
		win->zoom += 0.1;
		list_to_array(win->lines, win->map_size, win, win->map);
		if (!out_of_window(win))
			new_image(win);
		else
			win->zoom -= 0.1;
	}
	else if (keycode == 78 && win->zoom > 0)
	{
		win->zoom -= 0.1;
		list_to_array(win->lines, win->map_size, win, win->map);
		new_image(win);
	}
	if (keycode == 0)
	{
		win->teta += 0.1;
		list_to_array(win->lines, win->map_size, win, win->map);
		if (!out_of_window(win))
			new_image(win);
		else
			win->teta -= 0.1;
	}
	else if (keycode == 2)
	{
		win->teta -= 0.1;
		list_to_array(win->lines, win->map_size, win, win->map);
		if (!out_of_window(win))
			new_image(win);
		else
			win->teta += 0.1;
	}
	else if (keycode == 13)
	{
		win->z += 0.5;
		list_to_array(win->lines, win->map_size, win, win->map);
		if (!out_of_window(win))
			new_image(win);
		else
			win->z -= 0.5;
	}
	else if (keycode == 1)
	{
		win->z -= 0.5;
		list_to_array(win->lines, win->map_size, win, win->map);
		if (!out_of_window(win))
			new_image(win);
		else
			win->z += 0.5;
	}
	return (1);
}

void	new_image(t_window *window)
{
	t_image		*img;
	t_image		*t;

	img = (t_image *) malloc(sizeof(t_image));
	img->img = mlx_new_image(window->mlx, 2500, 1500);
	img->address = mlx_get_data_addr(img->img, &(img->bits), &(img->size), &(img->endian));
	t = window->image;
	window->image = img;
	draw_map(window->map, window);
	mlx_put_image_to_window (window->mlx, window->win, window->image->img, 0, 0);
	if (t)
	{
		mlx_destroy_image(window->mlx, t->img);
		free (t);
	}
}

int	main(int ac, char **av)
{
	t_window	*window;

	if (ac != 2)
		error_case(5);
	window = (t_window *) malloc(sizeof(t_window));
	window->image = NULL;
	window->map_size[0] = 0; //norme
	window->trans[0] = 0;
	window->trans[1] = 0;
	window->teta = 0.4;
	window->zoom = 2;
	window->z = 3;
	window->color = 0xFFFFFF;
	window->map = get_map(av[1], window->map_size, window);
	window->mlx = mlx_init();
	window->win = mlx_new_window(window->mlx, 2500, 1500, "fdf");
	// new_image(window);
	// mlx_hook(window->win, 2, 1L<<0, key_hook, window);
	// mlx_mouse_hook(window->win, mouse_hook, window);
	mlx_loop(window->mlx);
}