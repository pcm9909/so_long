// #include "./mlx/mlx.h"
// #include <stdio.h>
// #include <stdlib.h>

// # define UP_W				119
// # define DOWN_S				115
// # define LEFT_A				97
// # define RIGHT_D			100
// # define EXIT_ESC			65307
// # define EXIT_BUTTON		17

// typedef struct s_vars
// {
//     void *mlx;
//     void *win;
// }               t_vars;

// typedef struct s_data
// {
//     void	*img;
// 	char	*relative_path;
// 	int		img_width;
// 	int		img_height;
//     int     x;
//     int     y;
// }               t_data;


// //
// //keycode 는keysymdef.h 참고하기 
// int	key_hook(int keycode, t_data img)
// {
// 	if (keycode == UP_W)
//         img.y++;
//     else if (keycode == DOWN_S)
//         img.y--;
//     else if (keycode == LEFT_A)
//         img.x++;
//     else if (keycode == RIGHT_D)
//         img.x--;
//     else if (keycode == EXIT_ESC)
//         exit(0);
//     printf("%d %d\n", img.x, img.y);
// }

// int    t(){
//     exit(0);
// }

// int main()
// {
//     t_vars var;
//     t_data img;
//     img.x = 0;
//     img.y = 0;
//     img.relative_path = "./test3.xpm";
//     var.mlx = mlx_init();
//     var.win = mlx_new_window(var.mlx, 1080, 720, "hook test");
//     img.img = mlx_xpm_file_to_image(var.mlx, img.relative_path, &img.img_width, &img.img_height);
//     mlx_put_image_to_window(var.mlx, var.win, img.img, 10, 10);
//     mlx_key_hook(var.win, &key_hook, &var);
//     mlx_hook(var.win, 17, 0, t, &var);
//     mlx_loop_hook(var.mlx, key_hook, &var);
//     mlx_loop(var.mlx);
// }

#include <stdio.h>
#include <stdlib.h>
#include "mlx/mlx.h"

typedef struct s_param
{
	void	*mlx;
	void	*win;
	void	*c;
	int		fd;
	int		play_x;
	int		play_y;
	int		img_x;
	int		img_y;
	int		win_x;
	int		win_y;
}	t_param;

# define UP_W				119
# define DOWN_S				115
# define LEFT_A				97
# define RIGHT_D			100
# define EXIT_ESC			65307
# define EXIT_BUTTON		17

//mac
// #define UP_W 13
// #define DOWN_S 1
// #define LEFT_A 0
// #define RIGHT_D 2
// #define EXIT_ESC 53
// #define EXIT_BUTTON 17
int cnt = 0;
int	key_press(int keycode, t_param *p)
{
	
    printf("%d\n",cnt);
	if (keycode == UP_W && p->play_y != 0)
	{
		p->play_y -= p->img_y;
		cnt++;
	}
	if (keycode == DOWN_S && p->play_y != 700)
	{
		p->play_y += p->img_y;
		cnt++;
	}
	else if (keycode == LEFT_A && p->play_x != 0)
	{
		p->play_x -= p->img_x;
		cnt++;
	}
	else if (keycode == RIGHT_D && p->play_x != 900)
	{
		p->play_x += p->img_x;
		cnt++;
	}
	else if (keycode == EXIT_ESC)
		exit(0);
	else if (keycode == EXIT_BUTTON)
		exit(0);
	printf("x: %d y : %d\n", p->play_x, p->play_y);
	return (0);
}

int	draw(t_param *p)
{
	mlx_clear_window(p->mlx, p->win);
	mlx_put_image_to_window(p->mlx, p->win, p->c, p->play_x, p->play_y);
	return (0);
}

int	main(void)
{
	t_param		par;

	par.mlx = mlx_init();
	par.c = mlx_xpm_file_to_image(par.mlx, "test.xpm", &par.img_x, &par.img_y);
	par.win = mlx_new_window(par.mlx, 1000, 1000, "DrawMap");
	par.play_x = 0;
	par.play_y = 0;
	mlx_hook(par.win,2,1L<<0, key_press, &par);
	mlx_loop_hook(par.mlx, &draw, &par);
	mlx_loop(par.mlx);
	return (0);
}