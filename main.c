#include "fdf.h"

int	key_hook(int keycode, t_window *window)
{
	printf("%d\n", keycode);
	// if (keycode == 53)
	// {
	// 	// mlx_destroy_image(window->mlx, window->image->img);
	// 	printf("%d\n", mlx_destroy_window(window->mlx, window->win));
	// 	exit (0);
	// }
	return (1);
}
// int	my_close(int keycode, t_window *window)
// {

// 	// mlx_destroy_image(window->mlx, window->image->img);
// 	mlx_destroy_window(window->mlx, window->win);
// 	exit (0);
// }
int	main(int ac, char **av)
{
	t_point		**map;
	t_window	*window;
	t_image		*img;

	if (ac != 2)
		error_case(5);
	window = (t_window *) malloc(sizeof(t_window));
	window->map_size[0] = 0; //norme
	map = get_map(av[1], window->map_size, window);
	window->mlx = mlx_init();
	window->win = mlx_new_window(window->mlx, abs(window->min[1]) + abs(window->max[1]) + 20, abs(window->min[0]) + abs(window->max[0]) + 20, "fdf");
	// window->win = mlx_new_window(window->mlx, 1000, 1000, "fdf");
	img = (t_image *) malloc(sizeof(t_image));
	img->img = mlx_new_image(window->mlx, abs(window->min[1]) + abs(window->max[1]) + 20, abs(window->min[0]) + abs(window->max[0]) + 20);
	img->address = mlx_get_data_addr(img->img, &(img->bits), &(img->size), &(img->endian));
	window->image = img;
	window->color = 252;
	draw_map(map, window);
	mlx_put_image_to_window (window->mlx, window->win, window->image->img, 0, 0);
	mlx_key_hook(window->win, key_hook, window);
	// mlx_hook(window->win, 2, 1L<<0, my_close, window);
	// while (window->mlx)
	printf("%d - %d\n", window->map_size[1], window->map_size[0]);
	mlx_loop(window->mlx);
}