#include "fdf.h"

// void	mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color)
// {

// 	mlx_pixel_put(win->mlx, win->win, (abs(win->min[1]) + p[0] + 10), (abs(win->min[0]) + p[1] + 10), 0xFFFFFF);
// }

//p[0] == x && p[1] == y
static void	draw_segment(t_segment *seg, t_window *win, int dx, int dy)
{
	int		delta;
	int		p[2];
	char	*color;

	p[0] = seg->xi;
	p[1] = seg->yi;
	color = win->color;
	if (seg->color)
		color = seg->color;
	delta = 2 * dy - dx;
	while ((!seg->b && p[0] <= seg->xf) || (seg->b && p[1] <= seg->yf))
	{
		mlx_pixel_put(win->mlx, win->win, (abs(win->min[1]) + p[0] + 10), (abs(win->min[0]) + p[1] + 10), 0xFFFFFF);
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

static void	draw_segment_2(t_segment *seg, t_window *win, int dx, int dy)
{
	int		delta;
	int		p[2];
	char	*color;

	p[0] = seg->xi;
	p[1] = seg->yi;
	color = win->color;
	if (seg->color)
		color = seg->color;
	delta = 2 * dy - dx;
	while ((!seg->b && p[0] >= seg->xf) || (seg->b && p[1] <= seg->yf))
	{
		mlx_pixel_put(win->mlx, win->win, (abs(win->min[1]) + p[0] + 10), (abs(win->min[0]) + p[1] + 10), 0xFFFFFF);
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

void	draw(t_segment *seg, t_window *win)
{
	int	dx;
	int	dy;
	int t;
	int b = 0;

	dx = abs(seg->xf - seg->xi);
	dy = abs(seg->yf - seg->yi);
	seg->b = (dx < dy);

	if (((seg->xf < seg->xi) && (seg->yf < seg->yi)) || ((seg->xf >= seg->xi) && (seg->yf <= seg->yi)))
	{
		t = seg->xf;
		seg->xf = seg->xi;
		seg->xi = t;
		t = seg->yf;
		seg->yf = seg->yi;
		seg->yi = t;
	}

	if (((seg->xf >= seg->xi) && (seg->yf >= seg->yi)))
	{
		if (dx >= dy)
			draw_segment(seg, win, dx, dy);
		else
			draw_segment(seg, win, dy, dx);
	}
	else 			//	xf <= xi      ||     yf >= yi
	{
		if (dx >= dy)
			draw_segment_2(seg, win, dx, dy);
		else
			draw_segment_2(seg, win, dy, dx);
	}
}
