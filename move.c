#include "so_long.h"

void	move_forward(t_vars *p)
{
	if (p->map[p->player_y / BLOCK - 1][p->player_x / BLOCK] != '1')
	{
        mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
        p->player_y -= BLOCK;
        mlx_put_image_to_window(p->mlx, p->win, p->player_back, p->player_x, p->player_y);
        p->move++;
    }
}

void move_backward(t_vars *p)
{
    if (p->map[p->player_y / BLOCK + 1][p->player_x / BLOCK] != '1')
    {
        mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
        p->player_y += BLOCK;
        mlx_put_image_to_window(p->mlx, p->win, p->player_front, p->player_x, p->player_y);
        p->move++;
    }
}

void move_left(t_vars *p)
{
    if(p->map[p->player_y / BLOCK][p->player_x / BLOCK - 1] != '1')
    {
        mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
        p->player_x -= BLOCK;
        mlx_put_image_to_window(p->mlx, p->win, p->player_left, p->player_x, p->player_y);
        p->move++; 
    }
}

void move_right(t_vars *p)
{   
    if(p->map[p->player_y / BLOCK][p->player_x / BLOCK + 1] != '1')
    {
        mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
        p->player_x += BLOCK;
        mlx_put_image_to_window(p->mlx, p->win, p->player_right, p->player_x, p->player_y);
        p->move++;
    }
}
