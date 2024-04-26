/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:59:47 by chunpark          #+#    #+#             */
/*   Updated: 2024/04/26 03:38:51 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	draw_wall(t_vars *var, int i, int k)
{
	if (var->map[i][k] == '1')
		mlx_put_image_to_window(var->mlx, var->win, var->wall, var->w, var->h);
}

void	draw_tile(t_vars *var, int i, int k)
{
	if (var->map[i][k] == '0')
		mlx_put_image_to_window(var->mlx, var->win, var->tile, var->w, var->h);
}

void	draw_player(t_vars *var, int i, int k)
{
	if (var->map[i][k] == 'P')
	{
		var->player_x = var->w;
		var->player_y = var->h;
		mlx_put_image_to_window(var->mlx, var->win, var->player_front, \
				var->w, var->h);
	}
}

void	draw_collection(t_vars *var, int i, int k)
{
	if (var->map[i][k] == 'C')
		mlx_put_image_to_window(var->mlx, var->win, var->collection, \
				var->w, var->h);
}

void	draw_exit(t_vars *var, int i, int k)
{
	if (var->map[i][k] == 'E')
	{
		var->exit_x = var->w;
		var->exit_y = var->h;
		mlx_put_image_to_window(var->mlx, var->win, var->goal, var->w, var->h);
	}
}
