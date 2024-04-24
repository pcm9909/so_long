#include "so_long.h"

void xpm_input(t_vars *var)
{
    var->wall = mlx_xpm_file_to_image(var->mlx, "./img/wall.xpm", &var->img_width, &var->img_height);
    var->tile = mlx_xpm_file_to_image(var->mlx, "./img/tile.xpm", &var->img_width, &var->img_height);
    var->player_front = mlx_xpm_file_to_image(var->mlx, "./img/player_front.xpm", &var->img_width, &var->img_height);
    var->player_back = mlx_xpm_file_to_image(var->mlx, "./img/player_back.xpm", &var->img_width, &var->img_height);
    var->player_right = mlx_xpm_file_to_image(var->mlx, "./img/player_right.xpm", &var->img_width, &var->img_height);
    var->player_left = mlx_xpm_file_to_image(var->mlx, "./img/player_left.xpm", &var->img_width, &var->img_height);
    var->collection = mlx_xpm_file_to_image(var->mlx, "./img/collection.xpm", &var->img_width, &var->img_height);
    var->goal = mlx_xpm_file_to_image(var->mlx, "./img/exit.xpm", &var->img_width, &var->img_height);
    var->goal1 = mlx_xpm_file_to_image(var->mlx, "./img/exit1.xpm", &var->img_width, &var->img_height);
    var->enemy = mlx_xpm_file_to_image(var->mlx, "./img/enemy.xpm", &var->img_width, &var->img_height);
}