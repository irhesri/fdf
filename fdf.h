#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_line
{
	char			**points;
	struct s_line	*next;
} t_line ;

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

} t_window ;

void	ft_putstr_fd(char *s, int fd);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c, int *len);
int		error_case(void);
void    my_push_back(t_line **list, char **data);
int		my_atoi(char *str);

#endif