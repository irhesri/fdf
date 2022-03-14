#include "fdf.h"

void	draw_map(t_point **map, t_window *win)
{
	int			i;
	int			j;
	t_segment	*seg;

	i = -1;
	seg = malloc(sizeof(t_segment));
	!(seg) && error_case(0);
	while (++i < win->map_size[0])
	{
		j = -1;
		while (++j < win->map_size[1] - 1)
		{
			seg->color = (&map[i][j])->color;
			seg->xi = (&map[i][j])->x + abs(win->min[1]);
			seg->yi = (&map[i][j])->y + abs(win->min[0]);
			seg->xf = (&map[i][j + 1])->x + abs(win->min[1]);
			seg->yf = (&map[i][j + 1])->y + abs(win->min[0]);
			draw(seg, win);
			if (map[i + 1])
			{
				seg->xf = (&map[i + 1][j])->x + abs(win->min[1]);
				seg->yf = (&map[i + 1][j])->y + abs(win->min[0]);
				draw(seg, win);
			}
		}
		if (map[i + 1])
		{
			seg->xi = (&map[i][j])->x + abs(win->min[1]);			
			seg->xf = (&map[i + 1][j])->x + abs(win->min[1]);
			seg->yi = (&map[i][j])->y + abs(win->min[0]);
			seg->yf = (&map[i + 1][j])->y + abs(win->min[0]);
			draw(seg, win);
		}
	}
}

int	main(int ac, char **av)
{
	t_point		**map;
    t_window	*window;
	
	if (ac != 2)
		error_case(5);
    window = (t_window *) malloc(sizeof(t_window));
	map = get_map(av[1], window->map_size, window);
	window->mlx = mlx_init();
    window->win = mlx_new_window(window->mlx, abs(window->min[1]) + abs(window->max[1]) + 20, abs(window->min[0]) + abs(window->max[0]) + 20, "fdf");
	// window->image = mlx_new_image(window->mlx, abs(window->min[1]) + abs(window->max[1]) + 20, abs(window->min[0]) + abs(window->max[0]) + 20);
	// window->win = mlx_new_window(window->mlx, 2000, 1000, "fdf");
	t_segment *seg = malloc(sizeof(t_segment));
	window->color = 0xFFFFFF;

	seg->xi = 0;
	seg->yi = 500;
	seg->xf = 2000;
	seg->yf = 10;
	// draw(seg, window);
	// int i = -1,j;
	// while (map[++i])
	// {
	// 	j = 0;
	// 	while (j < window->map_size[1])
	// 	{
	// 		printf("%d ", (&map[i][j])->x);
	// 		j++;
	// 	}
	// 	printf("\n");
	// }
	draw_map(map, window);
	// mlx_put_image_to_window (window->mlx, window->win, window->image, 0, 0);
	mlx_loop(window->mlx);

	// mlx_destroy_image ( void *mlx_ptr, void *img_ptr );
}