/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:49:20 by chunpark          #+#    #+#             */
/*   Updated: 2024/04/25 14:52:50 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_x(t_vars *var)
{
	int	j;

	if (var->height < 3)
		exit_error("ERROR CODE 1 : The map is not valid\n");
	var->baselen = ft_strlen(var->map[0]);
	j = 1;
	while (j < var->height)
	{
		if (var->baselen != ft_strlen(var->map[j]))
			exit_error("ERROR CODE 2 : The map is not valid\n");
		j++;
	}
}

void	check_map_y(t_vars *var)
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

void	check_map_border(t_vars *var)
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

void	check_map_input_val(t_vars *var)
{
	int	i;
	int	j;

	var->cntE = 0;
	var->cntP = 0;
	var->cntC = 0;
	i = 1;
	while (i < var->height - 1)
	{
		j = 1;
		while (j < var->baselen - 1)
		{
			if (var->map[i][j] == 'C')
				var->cntC++;
			else if (var->map[i][j] == 'P')
				var->cntP++;
			else if (var->map[i][j] == 'E')
				var->cntE++;
			else if (var->map[i][j] == 'I')
				;
			else if (var->map[i][j] != '1' && var->map[i][j] != '0')
				exit_error("ERROR CODE 5 : The map is not valid\n");
			j++;
		}
		i++;
	}
	if (var->cntC < 1 || var->cntP != 1 || var->cntE != 1)
		exit_error("ERROR CODE 6 : The map is not valid\n");
}

void	check_map(t_vars *var)
{
	check_map_x(var);
	check_map_y(var);
	check_map_border(var);
	check_map_input_val(var);
}
