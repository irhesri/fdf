#include "fdf.h"

static void	draw_segment_up(t_segment *seg, t_image *img, int dx, int dy)
{
	int		delta;
	int		color;
	char	*dst;

	color = seg->color;
	delta = 2 * dy - dx;
	while ((!seg->b && seg->xi <= seg->xf) || (seg->b && seg->yi <= seg->yf))
	{
		dst = img->address + (seg->yi * img->size + seg->xi * img->bits / 8);
		*(unsigned int *) dst = color;
		if (delta < 0)
			delta += 2 * dy;
		else
		{
			delta += 2 * (dy - dx);
			!seg->b && seg->yi++;
			seg->b && seg->xi++;
		}
		!seg->b && seg->xi++;
		seg->b && seg->yi++;
	}
}

static void	draw_segment_down(t_segment *seg, t_image *img, int dx, int dy)
{
	int		delta;
	int		color;
	char	*dst;

	color = seg->color;
	delta = 2 * dy - dx;
	while ((!seg->b && seg->xi >= seg->xf) || (seg->b && seg->yi <= seg->yf))
	{
		dst = img->address + (seg->yi * img->size + seg->xi * img->bits / 8);
		*(unsigned int *) dst = color;
		if (delta < 0)
			delta += 2 * dy;
		else
		{
			delta += 2 * (dy - dx);
			!seg->b && seg->yi++;
			seg->b && seg->xi--;
		}
		!seg->b && seg->xi--;
		seg->b && seg->yi++;
	}
}

static void	seg_init(t_segment *seg, t_window *win, t_point *p0, t_point *p1)
{
	t_point	*p;
	int		dx;
	int		dy;

	if (p1->y < p0->y)
	{
		p = p0;
		p0 = p1;
		p1 = p;
	}
	seg->xi = p0->x + abs(win->min[1]) + 10;
	seg->yi = p0->y + abs(win->min[0]) + 10;
	seg->xf = p1->x + abs(win->min[1]) + 10;
	seg->yf = p1->y + abs(win->min[0]) + 10;
	dx = abs(seg->xf - seg->xi);
	dy = abs(seg->yf - seg->yi);
	seg->b = (dx < dy);
	if ((seg->xf >= seg->xi) && (dx >= dy))
		draw_segment_up(seg, win->image, dx, dy);
	else if (seg->xf >= seg->xi)
		draw_segment_up(seg, win->image, dy, dx);
	else if (dx >= dy)
		draw_segment_down(seg, win->image, dx, dy);
	else
		draw_segment_down(seg, win->image, dy, dx);
}

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
			seg->color = win->color;
			if ((&map[i][j])->color != -1)
				seg->color = (&map[i][j])->color;
			seg_init(seg, win, &map[i][j], &map[i][j + 1]);
			if (map[i + 1])
				seg_init(seg, win, &map[i][j], &map[i + 1][j]);
		}
		if (map[i + 1])
			seg_init(seg, win, &map[i][j], &map[i + 1][j]);
	}
	free (seg);
}
