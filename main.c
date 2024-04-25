/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:29:43 by chunpark          #+#    #+#             */
/*   Updated: 2024/04/25 21:37:37 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	// char a[10];
	// read(0,a,3);
	t_vars	var;

	var.move = 0;
	if (argc == 2)
	{
		if (ft_strncmp(ft_strchr(argv[1], '.'), ".ber\0", 5) == 0)
		{
			read_map(&var, argv[1]);
			check_map(&var);
			var.mlx = mlx_init();
			var.win = mlx_new_window(var.mlx, \
					var.baselen * BLOCK, var.height * BLOCK, "Pocketmon");
			draw_map(&var);
			check_player_path(&var);
			mlx_hook(var.win, 2, 1L << 0, key_press, &var);
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
