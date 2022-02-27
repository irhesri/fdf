#include <mlx.h>
#include "fdf.h"
#include <math.h>

void draw_segment(t_pixel *pi, t_pixel *pf, void *mlx, void *win) ////////////    dx  > dy
{
    int delta;
    int dx;
    int dy;
    t_pixel *p;

    p = (t_pixel *) malloc(sizeof(t_pixel)); ///-----> add allocatin protection
    dx = abs(pf->x - pi->x);
    dy = abs(pf->y - pi->y); 
    p->x = pi->x;
    p->y = pi->y;
    delta = 2 * dy - dx;
    while (p->x <= pf->x)
    {
        mlx_pixel_put(mlx, win, p->x, p->y, 0xf5f5f5);
        if (delta < 0)
            delta += 2 * dy;
        else
        {
            delta += 2 * (dy - dx);
            (p->y)++;
        }
        (p->x)++;
    }
}

int main(int ac, char **av)
{
    t_window *window;
    t_pixel *pi;
    t_pixel *pf;
    char    **map;

    //window = (t_window *) malloc(sizeof(t_window));



    /*
    pi = (t_pixel *) malloc(sizeof(t_pixel));
    pf = (t_pixel *) malloc(sizeof(t_pixel));

    pi -> x = 0;
    pi -> y = 0;
    pf -> x = 10;
    pf -> y = 10;

    window -> mlx = mlx_init();
    window -> win = mlx_new_window(window -> mlx, 500, 500, "mlx window");
    draw_segment(pi, pf, window -> mlx, window -> win); // dx must be bigger than
    mlx_loop(window -> mlx);*/
}