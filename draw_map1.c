/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:59:47 by chunpark          #+#    #+#             */
/*   Updated: 2024/04/25 20:02:20 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_wall(t_vars *var, int i, int k)
{
	if (var->map[i][k] == '1')
		mlx_put_image_to_window(var->mlx, var->win, var->wall, var->w, var->h);
}

void	handle_tile(t_vars *var, int i, int k)
{
	if (var->map[i][k] == '0')
		mlx_put_image_to_window(var->mlx, var->win, var->tile, var->w, var->h);
}

void	handle_player(t_vars *var, int i, int k)
{
	if (var->map[i][k] == 'P')
	{
		var->player_x = var->w;
		var->player_y = var->h;
		mlx_put_image_to_window(var->mlx, var->win, var->player_front, \
				var->w, var->h);
	}
}

void	handle_collection(t_vars *var, int i, int k)
{
	if (var->map[i][k] == 'C')
		mlx_put_image_to_window(var->mlx, var->win, var->collection, \
				var->w, var->h);
}

void	handle_exits(t_vars *var, int i, int k)
{
	if (var->map[i][k] == 'E')
	{
		var->exit_x = var->w;
		var->exit_y = var->h;
		mlx_put_image_to_window(var->mlx, var->win, var->goal, var->w, var->h);
	}
}
