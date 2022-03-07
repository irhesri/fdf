#include "fdf.h"

void	draw_map(t_point **map, t_window *win)
{
	int			i;
	int			j;
	t_segment	*seg;

	i = -1;
	seg = malloc(sizeof(t_segment));
	!(seg) && error_case();
	while (map[++i])
	{
		j = -1;
		while ((++j + 1) < win->map_size[1])
		{
			seg->color = (&map[i][j])->color;
			seg->xi = (&map[i][j])->x;
			seg->yi = (&map[i][j])->y;
			seg->xf = (&map[i][j + 1])->x;
			seg->yf = (&map[i][j + 1])->y;
			draw(seg, win);
			if (map[i + 1])
			{
				seg->xf = (&map[i + 1][j])->x;
				seg->yf = (&map[i + 1][j])->y;
				draw(seg, win);
			}
		}
		if (map[i + 1])
		{
			seg->xi = (&map[i][j])->x;			
			seg->xf = (&map[i][j])->x;
			seg->yi = (&map[i][j])->y;
			seg->yf = (&map[i + 1][j])->y;
		}
		draw(seg, win);
	}
}

int	main(int ac, char **av)
{
	t_point		**map;
    t_window	*window;
	
	if (ac != 2)
		error_case();
    window = (t_window *) malloc(sizeof(t_window));
	map = get_map(av[1], window -> map_size);
	window -> mlx = mlx_init();
    window -> win = mlx_new_window(window -> mlx, 1500, 1000, "fdf");
	window -> color = get_color();
	window -> t_x = 0;
	window -> t_y = 0;
	draw_map(map, window);
	mlx_loop(window -> mlx);
}