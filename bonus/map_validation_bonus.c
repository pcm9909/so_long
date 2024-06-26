/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:49:20 by chunpark          #+#    #+#             */
/*   Updated: 2024/04/26 03:38:58 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	validate_map_width(t_vars *var)
{
	int	j;

	if (var->height < 3)
		exit_error("ERROR CODE 1 : The map is not valid\n");
	var->baselen = ft_strlen(var->map[0]);
	j = 1;
	while (j < var->height)
	{
		if (var->baselen != (int)ft_strlen(var->map[j]))
			exit_error("ERROR CODE 2 : The map is not valid\n");
		j++;
	}
}

void	validate_map_height(t_vars *var)
{
	int	i;

	i = 0;
	while (i < var->baselen)
	{
		if (var->map[0][i] != '1' || var->map[var->height - 1][i] != '1')
			exit_error("ERROR CODE 3 : The map is not valid\n");
		i++;
	}
}

void	validate_map_border(t_vars *var)
{
	int	i;

	i = 0;
	while (i < var->height)
	{
		if (var->map[i][0] != '1' || var->map[i][var->baselen - 1] != '1')
			exit_error("ERROR CODE 4 : The map is not valid\n");
		i++;
	}
}

void	validate_map_elements(t_vars *var)
{
	int	i;
	int	j;

	var->cnt_e = 0;
	var->cnt_p = 0;
	var->cnt_c = 0;
	i = 0;
	while (++i < var->height - 1)
	{
		j = 0;
		while (++j < var->baselen - 1)
		{
			if (var->map[i][j] == 'C')
				var->cnt_c++;
			else if (var->map[i][j] == 'P')
				var->cnt_p++;
			else if (var->map[i][j] == 'E')
				var->cnt_e++;
			else if (var->map[i][j] != '1' && var->map[i][j] != '0' && \
					var->map[i][j] != 'I')
				exit_error("ERROR CODE 5 : The map is not valid\n");
		}
	}
	if (var->cnt_c < 1 || var->cnt_p != 1 || var->cnt_e != 1)
		exit_error("ERROR CODE 6 : The map is not valid\n");
}

void	validate_map_structure(t_vars *var)
{
	validate_map_width(var);
	validate_map_height(var);
	validate_map_border(var);
	validate_map_elements(var);
}
