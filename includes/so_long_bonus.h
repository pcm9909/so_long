/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:01:09 by chunpark          #+#    #+#             */
/*   Updated: 2024/04/26 16:01:30 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../utils/libft/libft.h"
# include "../utils/get_next_line/get_next_line.h"
# include "../mlx/mlx.h"
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
}				t_vars;

void	exit_error(char *str);

//map_validation_bonus.c
void	validate_map_width(t_vars *var);
void	validate_map_height(t_vars *var);
void	validate_map_border(t_vars *var);
void	validate_map_elements(t_vars *var);
void	validate_map_structure(t_vars *var);

//player_movements_bonus.c
void	move_forward(t_vars *p);
void	move_backward(t_vars *p);
void	move_left(t_vars *p);
void	move_right(t_vars *p);

//load_map_bonus.c
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	load_map_from_file(t_vars *p, char *filename);

//put_img_bonus.c
void	load_player_image(t_vars *var);
void	load_structure_image(t_vars *var);
void	load_image(t_vars *var);

//draw_map_1_bonus.c draw_map_2_bonus.c
void	draw_wall(t_vars *var, int i, int k);
void	draw_tile(t_vars *var, int i, int k);
void	draw_player(t_vars *var, int i, int k);
void	draw_collection(t_vars *var, int i, int k);
void	draw_exit(t_vars *var, int i, int k);
void	draw_enemy(t_vars *var, int i, int k);
void	draw_map(t_vars *var);

//key_press_handler_bonus.c
void	display_move_cnt(t_vars *p);
void	process_exit_conditions(t_vars *p);
int		process_key_press(int keycode, t_vars *p);

//map_verification_bonus.c
char	**create_dfs_map_copy(t_vars *var);
void	free_map_memory(char **map);
int		dfs(char **map, int x, int y, char find);
void	validate_player_path(t_vars *var);

#endif
