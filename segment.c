#include "fdf.h"

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
		mlx_pixel_put(win->mlx, win->win, p[0], p[1], (int)win->color);
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

void	draw(t_segment *seg, t_window *win)
{
	int	dx;
	int	dy;

	dx = abs(seg->xf - seg->xi);
	dy = abs(seg->yf - seg->yi);
	seg->b = (dx < dy);
	if (dx >= dy)
		draw_segment(seg, win, dx, dy);
	else
		draw_segment(seg, win, dy, dx);
}
