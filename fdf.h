/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:13:44 by irhesri           #+#    #+#             */
/*   Updated: 2022/03/17 21:13:47 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

typedef struct s_line
{
	char			**points;
	struct s_line	*next;
}t_line;

typedef struct s_segment
{
	int		xi;
	int		yi;
	int		xf;
	int		yf;
	short	b;
	int		color;
}t_segment;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}t_point;

typedef struct s_image
{
	void	*img;
	char	*address;
	int		bit;
	int		size;
	int		endian;
}t_image;

typedef struct s_window
{
	t_point	**map;
	t_line	*lines;
	t_image	*image;
	void	*mlx;
	void	*win;
	int		color;
	int		map_size[2];
	int		min[2];
	int		max[2];
}t_window;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c, int *len);
int		my_atoi(char *str, t_point *point);
void	ft_putstr_fd(char *s, int fd);
/*************************************NEW*************************************/
t_point	**get_map(char *file, int *size, t_window *win);
void	list_to_array(t_line *line, t_window *win, t_point **map, short b);
int		error_case(short n);
void	draw_map(t_point **map, t_window *win);

#endif
