/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:29:43 by chunpark          #+#    #+#             */
/*   Updated: 2024/04/26 03:38:56 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	close_win(void)
{
	exit(0);
}

void	exit_error(char *str)
{
	ft_putstr_fd(str, 1);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_vars	var;

	var.move = 0;
	if (argc == 2)
	{
		if (ft_strncmp(ft_strchr(argv[1], '.'), ".ber\0", 5) == 0)
		{
			load_map_from_file(&var, argv[1]);
			validate_map_structure(&var);
			var.mlx = mlx_init();
			var.win = mlx_new_window(var.mlx, \
					var.baselen * BLOCK, var.height * BLOCK, "Pocketmon");
			draw_map(&var);
			validate_player_path(&var);
			mlx_hook(var.win, 2, 1L << 0, process_key_press, &var);
			mlx_hook(var.win, 17, 0, close_win, &var);
			mlx_loop(var.mlx);
			exit(0);
		}
		else
			exit_error("ERROR CODE 9 : Please enter the [.ber] file\n");
	}
	else
		exit_error("ERROR CODE 10 : The number of inputs is not correct\n");
	exit(0);
}
