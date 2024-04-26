/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:48:30 by chunpark          #+#    #+#             */
/*   Updated: 2024/04/26 13:38:28 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	display_move_cnt(t_vars *p)
{
	char	*move_cnt;

	move_cnt = ft_itoa(p->move);
	mlx_string_put(p->mlx, p->win, 10, 20, 0xFFFFFF, move_cnt);
	free(move_cnt);
}

void	process_exit_conditions(t_vars *p)
{
	if (p->map[p->player_y / BLOCK][p->player_x / BLOCK] == 'C')
	{
		p->cnt_c--;
		p->map[p->player_y / BLOCK][p->player_x / BLOCK] = '0';
	}
	if (p->cnt_c == 0)
	{
		p->map[p->exit_y / BLOCK][p->exit_x / BLOCK] = 'E';
		mlx_put_image_to_window(p->mlx, p->win, p->goal1, p->exit_x, p->exit_y);
	}
	if (p->map[p->player_y / BLOCK][p->player_x / BLOCK] == 'I')
		exit(0);
	if (p->cnt_c == 0 && \
			p->map[p->player_y / BLOCK][p->player_x / BLOCK] == 'E')
		exit(0);
}

int	process_key_press(int keycode, t_vars *p)
{
	mlx_put_image_to_window(p->mlx, p->win, p->wall, 0, 0);
	if (p->cnt_c > 0)
		p->map[p->exit_y / BLOCK][p->exit_x / BLOCK] = '1';
	if (keycode == UP_W)
		move_forward(p);
	else if (keycode == DOWN_S)
		move_backward(p);
	else if (keycode == LEFT_A)
		move_left(p);
	else if (keycode == RIGHT_D)
		move_right(p);
	if (keycode == EXIT_ESC)
		exit(0);
	display_move_cnt(p);
	process_exit_conditions(p);
	return (0);
}
