/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:58:52 by chunpark          #+#    #+#             */
/*   Updated: 2024/04/26 03:38:57 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	**create_dfs_map_copy(t_vars *var)
{
	char	**dfs_maps;
	int		i;

	i = 0;
	dfs_maps = (char **)malloc(sizeof(char *) * (var->height + 1));
	while (i < var->height)
	{
		dfs_maps[i] = malloc(var->baselen + 1);
		ft_memcpy(dfs_maps[i], var->map[i], var->baselen + 1);
		i++;
	}
	dfs_maps[i] = NULL;
	return (dfs_maps);
}

void	free_map_memory(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	dfs(char **map, int x, int y, char find)
{
	int	cnt;

	cnt = 0;
	if (find == 'C')
	{
		if (map[y][x] == '1' || map[y][x] == 'E' || map[y][x] == 'I')
			return (0);
	}
	else
	{
		if (map[y][x] == '1' || map[y][x] == 'I')
			return (0);
	}
	if (map[y][x] != '1')
	{
		if (map[y][x] == find)
			cnt++;
		map[y][x] = '1';
		cnt += dfs(map, x - 1, y, find);
		cnt += dfs(map, x, y + 1, find);
		cnt += dfs(map, x + 1, y, find);
		cnt += dfs(map, x, y - 1, find);
		return (cnt);
	}
	return (0);
}

void	validate_player_path(t_vars *var)
{
	char	**map1;
	char	**map2;

	map1 = create_dfs_map_copy(var);
	map2 = create_dfs_map_copy(var);
	if (dfs(map1, var->player_x / BLOCK, var->player_y / BLOCK, 'E') != 1)
		exit_error("ERROR CODE 7 : The map is not valid\n");
	if (dfs(map2, var->player_x / BLOCK, var->player_y / BLOCK, \
				'C') != var->cnt_c)
		exit_error("ERROR CODE 8 : The map is not valid\n");
	free_map_memory(map1);
	free_map_memory(map2);
}
