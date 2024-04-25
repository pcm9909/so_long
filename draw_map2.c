/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:01:30 by chunpark          #+#    #+#             */
/*   Updated: 2024/04/25 20:01:33 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_enemy(t_vars *var, int i, int k)
{
	if (var->map[i][k] == 'I')
		mlx_put_image_to_window(var->mlx, var->win, var->enemy, var->w, var->h);
}

void	draw_map(t_vars *var)
{
	int	i;
	int	k;

	xpm_put(var);
	var->h = 0;
	i = 0;
	while (i < var->height)
	{
		var->w = 0;
		k = 0;
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
