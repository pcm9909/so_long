#include "so_long.h"

void handle_wall(t_vars *var, int i, int k)
{
    if (var->map[i][k] == '1')
        mlx_put_image_to_window(var->mlx, var->win, var->wall, var->w, var->h);
}

void handle_tile(t_vars *var, int i, int k)
{
    if (var->map[i][k] == '0')
        mlx_put_image_to_window(var->mlx, var->win, var->tile, var->w, var->h);
}

void handle_player(t_vars *var, int i, int k)
{
    if (var->map[i][k] == 'P')
    {
        var->player_x = var->w;
        var->player_y = var->h;
        mlx_put_image_to_window(var->mlx, var->win, var->player_front, var->w, var->h);
    }
}

void handle_collection(t_vars *var, int i, int k)
{
    if (var->map[i][k] == 'C')
        mlx_put_image_to_window(var->mlx, var->win, var->collection, var->w, var->h);
}

void handle_exits(t_vars *var, int i, int k)
{
    if (var->map[i][k] == 'E')
    {
        var->exit_x = var->w;
        var->exit_y = var->h;
        mlx_put_image_to_window(var->mlx, var->win, var->goal, var->w, var->h);
    }
}

void handle_enemy(t_vars *var, int i, int k)
{
    if (var->map[i][k] == 'I')
        mlx_put_image_to_window(var->mlx, var->win, var->enemy, var->w, var->h);
}

void draw_map(t_vars *var)
{
    xpm_input(var);
    var->h = 0;
    int i = 0;
    while (i < var->height)
    {
        var->w = 0;
        int k = 0;
        while (k < var->baselen)
        {
            handle_wall(var, i, k);
            handle_tile(var, i, k);
            handle_player(var, i, k);
            handle_collection(var, i, k);
            handle_exits(var, i, k);
            handle_enemy(var, i, k);
            var->w += BLOCK;
            k++;
        }
        var->h += BLOCK;
        i++;
    }
}