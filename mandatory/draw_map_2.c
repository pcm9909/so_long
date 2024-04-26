/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:01:30 by chunpark          #+#    #+#             */
/*   Updated: 2024/04/26 03:41:02 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	draw_map(t_vars *var)
{
	int	i;
	int	k;

	load_image(var);
	var->h = 0;
	i = 0;
	while (i < var->height)
	{
		var->w = 0;
		k = 0;
		while (k < var->baselen)
		{
			draw_wall(var, i, k);
			draw_tile(var, i, k);
			draw_player(var, i, k);
			draw_collection(var, i, k);
			draw_exit(var, i, k);
			var->w += BLOCK;
			k++;
		}
		var->h += BLOCK;
		i++;
	}
}
