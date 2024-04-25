/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:14:53 by chunpark          #+#    #+#             */
/*   Updated: 2024/04/26 03:38:59 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	load_player_image(t_vars *var)
{
	var->player_front = mlx_xpm_file_to_image(var->mlx, \
			"./img/player_front.xpm", &var->img_width, &var->img_height);
	var->player_back = mlx_xpm_file_to_image(var->mlx, \
			"./img/player_back.xpm", &var->img_width, &var->img_height);
	var->player_right = mlx_xpm_file_to_image(var->mlx, \
			"./img/player_right.xpm", &var->img_width, &var->img_height);
	var->player_left = mlx_xpm_file_to_image(var->mlx, \
			"./img/player_left.xpm", &var->img_width, &var->img_height);
}

void	load_structure_image(t_vars *var)
{
	var->wall = mlx_xpm_file_to_image(var->mlx, \
			"./img/wall.xpm", &var->img_width, &var->img_height);
	var->tile = mlx_xpm_file_to_image(var->mlx, \
			"./img/tile.xpm", &var->img_width, &var->img_height);
	var->collection = mlx_xpm_file_to_image(var->mlx, \
			"./img/collection.xpm", &var->img_width, &var->img_height);
	var->goal = mlx_xpm_file_to_image(var->mlx, \
			"./img/exit.xpm", &var->img_width, &var->img_height);
	var->goal1 = mlx_xpm_file_to_image(var->mlx, \
			"./img/exit1.xpm", &var->img_width, &var->img_height);
	var->enemy = mlx_xpm_file_to_image(var->mlx, \
			"./img/enemy.xpm", &var->img_width, &var->img_height);
}

void	load_image(t_vars *var)
{
	load_structure_image(var);
	load_player_image(var);
}
