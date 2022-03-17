#ifndef FDF_H
# define FDF_H

# include <stdio.h> /***************************************/

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>

typedef struct s_line
{
	char			**points;
	struct s_line	*next;
} t_line ;

typedef struct s_segment
{
	int		xi;
	int		yi;
	int		xf;
	int		yf;
	short	b;
	int		color;
} t_segment ;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
} t_point ;

typedef struct s_image
{
	void	*img;
	char	*address;
	int		bits;
	int		size;
	int		endian;
} t_image ;

typedef struct s_window
{
	void	*mlx;
	void	*win;
	t_image	*image;
	int		color;
	// y - x
	int		map_size[2];
	int		min[2];
	int		max[2];
} t_window ;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c, int *len);
int		error_case(short n);
void	draw_map(t_point **map, t_window *win);


int		my_atoi(char *str, t_point *point);
/************************NEW*******************************/
t_point	**get_map(char *file, int *size, t_window *win);
char	*get_color(void);

#endif