/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:13:44 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/13 23:43:10 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# ifdef __linux__
#  include "mlx_linux/mlx_linux.h"
# else
#  include "mlx_mac/mlx_mac.h"
# endif

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
	int		n[2];
	int		x[2];
	int		trans[2];
	float	z;
	float	zoom;
	double	teta;
	short	p;
}t_window;

int		my_atoi(char *str, t_point *point);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c, int *len);
size_t	ft_strlen(const char *str);
/*************************************NEW*************************************/
int		error_case(short n);
void	check_args(char *str, int ac);
void	new_image(t_window *window, int width, int length);
void	list_to_array(t_line *line, t_window *win, t_point **map, short b);
t_point	**get_map(char *file, int *size, t_window *win);

#endif
