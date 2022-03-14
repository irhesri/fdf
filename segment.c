#include "fdf.h"

// void	mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color)
// {

// 	mlx_pixel_put(win->mlx, win->win, (abs(win->min[1]) + p[0] + 10), (abs(win->min[0]) + p[1] + 10), 0xFFFFFF);
// }

//p[0] == x && p[1] == y
static void	draw_segment_up(t_segment *seg, t_window *win, int dx, int dy)
{
	int		delta;
	int		p[2];
	int		color;

	p[0] = seg->xi;
	p[1] = seg->yi;
	color = win->color;
	if (seg->color != -1)
		color = seg->color;
	delta = 2 * dy - dx;
	while ((!seg->b && p[0] <= seg->xf) || (seg->b && p[1] <= seg->yf))
	{
		mlx_pixel_put(win->mlx, win->win, p[0] + 10,  + p[1] + 10, color);
		if (delta < 0)
			delta += 2 * dy;
		else
		{
			delta += 2 * (dy - dx);
			!seg->b && p[1]++;
			seg->b && p[0]++;
		}
		!seg->b && p[0]++;
		seg->b && p[1]++;
	}
}

static void	draw_segment_down(t_segment *seg, t_window *win, int dx, int dy)
{
	int		delta;
	int		p[2];
	int		color;

	p[0] = seg->xi;
	p[1] = seg->yi;
	color = win->color;
	if (seg->color != -1)
		color = seg->color;
	delta = 2 * dy - dx;
	while ((!seg->b && p[0] >= seg->xf) || (seg->b && p[1] <= seg->yf))
	{
		mlx_pixel_put(win->mlx, win->win, p[0] + 10, p[1] + 10, color);
		if (delta < 0)
			delta += 2 * dy;
		else
		{
			delta += 2 * (dy - dx);
			!seg->b && p[1]++;
			seg->b && p[0]--;
		}
		!seg->b && p[0]--;
		seg->b && p[1]++;
	}
}

static void	my_swap(t_segment *seg)
{
	seg->xi = seg->xi + seg->xf;
	seg->xf = seg->xi - seg->xf;
	seg->xi = seg->xi - seg->xf;
	seg->yi = seg->yi + seg->yf;
	seg->yf = seg->yi - seg->yf;
	seg->yi = seg->yi - seg->yf;
}

void	draw(t_segment *seg, t_window *win)
{
	int	dx;
	int	dy;
	int b;
	
	b = 0;
	dx = abs(seg->xf - seg->xi);
	dy = abs(seg->yf - seg->yi);
	seg->b = (dx < dy);
	if (((seg->xf < seg->xi && seg->yf < seg->yi) || (seg->xf >= seg->xi && seg->yf <= seg->yi)) && ++b)
		my_swap(seg);
	if ((seg->xf >= seg->xi) && (seg->yf >= seg->yi) && (dx >= dy))
			draw_segment_up(seg, win, dx, dy);
	else if ((seg->xf >= seg->xi) && (seg->yf >= seg->yi))
			draw_segment_up(seg, win, dy, dx);
	else if (dx >= dy)
		draw_segment_down(seg, win, dx, dy);
	else
		draw_segment_down(seg, win, dy, dx);
	if (b)
		my_swap(seg);
}
