/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:14:27 by irhesri           #+#    #+#             */
/*   Updated: 2022/03/17 21:14:30 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	draw_segment_up(t_segment *seg, t_image *img, int dx, int dy)
{
	int		delta;
	int		color;
	char	*dst;

	color = seg->color;
	delta = 2 * dy - dx;
	while ((!seg->b && seg->xi <= seg->xf) || (seg->b && seg->yi <= seg->yf))
	{
		dst = img->address + (seg->yi * img->size + seg->xi * img->bit / 8);
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
		dst = img->address + (seg->yi * img->size + seg->xi * img->bit / 8);
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
	seg->xi = p0->x + abs(win->n[1]) * ((win->n[1] < 0) - (win->n[1] > 0)) + 1;
	seg->yi = p0->y + abs(win->n[0]) * ((win->n[0] < 0) - (win->n[0] > 0)) + 1;
	seg->xf = p1->x + abs(win->n[1]) * ((win->n[1] < 0) - (win->n[1] > 0)) + 1;
	seg->yf = p1->y + abs(win->n[0]) * ((win->n[0] < 0) - (win->n[0] > 0)) + 1;
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

static void	draw_map(t_point **map, t_window *win)
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

void	new_image(t_window *win, int width, int length)
{
	t_image		*img;
	t_image		*t;
	char		*a;

	img = (t_image *) malloc(sizeof(t_image));
	img->img = mlx_new_image(win->mlx, width, length);
	a = mlx_get_data_addr(img->img, &(img->bit), &(img->size), &(img->endian));
	img->address = a;
	t = win->image;
	win->image = img;
	draw_map(win->map, win);
	mlx_clear_window(win->mlx, win->win);
	mlx_put_image_to_window (win->mlx, win->win, img->img,
		win->trans[1], win->trans[0]);
	if (t)
	{
		mlx_destroy_image(win->mlx, t->img);
		free (t);
	}
}
