/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:53:25 by chunpark          #+#    #+#             */
/*   Updated: 2024/04/25 20:11:21 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include "./mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# define BLOCK 64

//for linux
# define UP_W				119
# define DOWN_S				115
# define LEFT_A				97
# define RIGHT_D			100
# define EXIT_ESC			65307
# define EXIT_BUTTON		17

// //for mac
// #define UP_W 13
// #define DOWN_S 1
// #define LEFT_A 0
// #define RIGHT_D 2
// #define EXIT_ESC 53
// #define EXIT_BUTTON 17
typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*wall;
	void	*tile;
	void	*collection;
	void	*enemy;
	void	*player_front;
	void	*player_back;
	void	*player_right;
	void	*player_left;
	void	*goal;
	void	*goal1;
	int		img_width;
	int		img_height;
	char	**map;
	char	**dfs_maps;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		baselen;
	int		height;
	int		h;
	int		w;
	int		cnt_e;
	int		cnt_p;
	int		cnt_c;
	int		move;
	int		step;
}				t_vars;

void	exit_error(char *str);

//checkmap.c
void	check_map_x(t_vars *var);
void	check_map_y(t_vars *var);
void	check_map_border(t_vars *var);
void	check_map_input_val(t_vars *var);
void	check_map(t_vars *var);

//move.c
void	move_forward(t_vars *p);
void	move_backward(t_vars *p);
void	move_left(t_vars *p);
void	move_right(t_vars *p);

//read_map.c
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	read_map(t_vars *p, char *filename);

//put_img.c
void	xpm_put_player(t_vars *var);
void	xpm_put_structure(t_vars *var);
void	xpm_put(t_vars *var);

//draw_map1.c draw_map2.c
void	handle_wall(t_vars *var, int i, int k);
void	handle_tile(t_vars *var, int i, int k);
void	handle_player(t_vars *var, int i, int k);
void	handle_collection(t_vars *var, int i, int k);
void	handle_exits(t_vars *var, int i, int k);
void	handle_enemy(t_vars *var, int i, int k);
void	draw_map(t_vars *var);

//key_press.c
void	show_cnt(t_vars *p);
void	handle_exit(t_vars *p);
int		key_press(int keycode, t_vars *p);

//verification_map.c
char	**make_dfs_map(t_vars *var);
int		dfs(char **map, int x, int y, char find);
void	check_player_path(t_vars *var);

#endif
