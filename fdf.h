#ifndef FDF_H
# define FDF_H

# include <stdio.h> /***************************************/

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>

typedef struct s_pixel
{
    int x;
    int y;
} t_pixel;

typedef struct s_line
{
    char            **line;
    struct s_line   *next;
} t_line;

typedef struct s_window
{
    void *mlx;
    void *win;
    int color;
} t_window;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c, int *len);
int     my_strcmp(char *s1, char *s2);
int     my_atoi(char *str);

t_line  *get_map(char *file);

#endif