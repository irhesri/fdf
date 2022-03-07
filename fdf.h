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
	char	*color;
	int		zoom;
	int		t_x; //translate
	int		t_y;
	int		map_size[2];
} t_window ;

void	ft_putstr_fd(char *s, int fd);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c, int *len);
int		error_case(void);
void    my_push_back(t_line **list, char **data);



int		my_atoi(char *str, t_point *point);


void	draw(t_segment *seg, t_window *win);
/************************NEW*******************************/
t_point	**get_map(char *file, int *size);
char	*get_color(void);

#endif