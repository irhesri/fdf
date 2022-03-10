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
	char	*color;
} t_segment ;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	char	*color;
} t_point ;

typedef struct s_window
{
	void	*mlx;
	void	*win;
	void	*image;
	char	*color;
	// y - x
	int		map_size[2];
	int		min[2];
	int		max[2];
} t_window ;

void	ft_putstr_fd(char *s, int fd);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c, int *len);
int		error_case(short n);
void    my_push_back(t_line **list, char **data);



int		my_atoi(char *str, t_point *point);


void	draw(t_segment *seg, t_window *win);
// void	mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);;
/************************NEW*******************************/
t_point	**get_map(char *file, int *size, t_window *win);
char	*get_color(void);

#endif