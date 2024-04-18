#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include "./mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define BLOCK 64


//for linux
// # define UP_W				119
// # define DOWN_S				115
// # define LEFT_A				97
// # define RIGHT_D			100
// # define EXIT_ESC			65307
// # define EXIT_BUTTON		17


//for mac
#define UP_W 13
#define DOWN_S 1
#define LEFT_A 0
#define RIGHT_D 2
#define EXIT_ESC 53
#define EXIT_BUTTON 17

typedef struct s_vars
{
    void    *mlx;
    void    *win;
    void	*wall;
    void    *tile;
    void    *collection;
    void    *player;
    void    *goal;
	int		img_width;
	int		img_height;
    char    **map;
    int     player_x;
    int     player_y;
}               t_vars;



void *ft_realloc(void *ptr, size_t size)
{
    void *new_ptr;

    if (ptr == NULL)
        return (malloc(size));
    if (!size)
        return (ptr);
    new_ptr = malloc(size);
    ft_memcpy(new_ptr, ptr, size);
    return (new_ptr);
}

int key_press(int keycode, t_vars *p)
{
    printf("keycode : %d\n", keycode);
    if (keycode == UP_W && p->player_y != BLOCK)
    {
        mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
        p->player_y -= BLOCK;
        mlx_put_image_to_window(p->mlx, p->win, p->player, p->player_x, p->player_y);
    }
    if (keycode == DOWN_S && p->player_y != 700 - BLOCK)
    {
        mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
        p->player_y += BLOCK;
        mlx_put_image_to_window(p->mlx, p->win, p->player, p->player_x, p->player_y);
    }
    else if (keycode == LEFT_A && p->player_x != BLOCK)
    {
        mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
        p->player_x -= BLOCK;
        mlx_put_image_to_window(p->mlx, p->win, p->player, p->player_x, p->player_y);
    }
    else if (keycode == RIGHT_D && p->player_x != 576)
    {
        mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
        p->player_x += BLOCK;
        mlx_put_image_to_window(p->mlx, p->win, p->player, p->player_x, p->player_y);
    }

    else if (keycode == EXIT_ESC)
        exit(0);
    else if (keycode == EXIT_BUTTON)
        exit(0);
    printf("x: %d y : %d\n", p->player_x, p->player_y);
    return (0);
}

int    t(){
   exit(0);
}



int main(int argc, char **argv)
{
    int fd;
    char *line;
    int height = 0;
    t_vars  var;

    if (argc == 2)
    {
        if (ft_strncmp(ft_strchr(argv[1], '.'), ".ber", 4) == 0) // .ber파일인지 검증
        {
            fd = open(argv[1], O_RDONLY);
            var.map = (char **)malloc(sizeof(char *));
            while ((line = get_next_line(fd)) > 0) //.ber파일을 이중배열로 만듬
            {
                var.map[height] = ft_strdup(line);
                free(line);
                height++;
                var.map = (char **)ft_realloc(var.map, (height + 1) * sizeof(char *));
            }
            // map이 제대로 적성되었는지 검증 1. x축이 잘 들어왔는가? map이 3줄 이상인가
            if (height < 3)
                printf("error height\n");
            int baselen = ft_strlen(var.map[0]) - 1;
            int j = 1;
            printf("%d %d\n", height, baselen);
            while (j < height)
            {
                printf("%d\n", ft_strlen(var.map[j]) - 1);
                if (baselen != ft_strlen(var.map[j]) - 1)
                {
                    if (j == height - 1)
                    {
                        if (baselen == ft_strlen(var.map[j]))
                            break;
                    }
                    printf("error base\n");
                    break;
                }
                j++;
            }
            // map이 제대로 적성되었는지 검증 2. y축이 잘 들어왔는가? map이 3줄 이상인가
            int i = 0;
            while (i < baselen)
            {
                if (var.map[0][i] != '1' || var.map[height - 1][i] != '1')
                {
                    printf("error 1\n");
                    break;
                }
                i++;
            }
            //check 테두리
            i = 0;
            while (i < height)
            {
                if (var.map[i][0] != '1' || var.map[i][baselen - 1] != '1')
                {
                    printf("error 2\n");
                    break;
                }
                i++;
            }
            int cntC = 0, cntP = 0, cntE = 0;
            i = 1;
            while (i < height - 1)
            {
                int j = 1;
                while (j < baselen - 1)
                {
                    if (var.map[i][j] == 'C')
                        cntC++;
                    else if (var.map[i][j] == 'P')
                        cntP++;
                    else if (var.map[i][j] == 'E')
                        cntE++;
                    else if (var.map[i][j] != '1' && var.map[i][j] != '0')
                    {
                        printf("bad input\n");
                        return 0;
                    }
                    j++;
                }
                i++;
            }
            if (cntC < 1 || cntP != 1 || cntE != 1)
            {
                printf("error C\n");
                return (0);
            }
            var.mlx = mlx_init();
            var.win = mlx_new_window(var.mlx, baselen * BLOCK, height * BLOCK, "img test");
            //1
            var.wall = mlx_xpm_file_to_image(var.mlx, "./img/wall.xpm", & var.img_width, &var.img_height);
            //0
            var.tile = mlx_xpm_file_to_image(var.mlx, "./img/tile.xpm", &var.img_width, &var.img_height);
            //P
            var.player = mlx_xpm_file_to_image(var.mlx, "./img/player.xpm", &var.img_width, &var.img_height);
            //C
            var.collection = mlx_xpm_file_to_image(var.mlx, "./img/collection.xpm", &var.img_width, &var.img_height);
            //E
            var.goal = mlx_xpm_file_to_image(var.mlx, "./img/exit.xpm", &var.img_width, &var.img_height);
            int h = 0;
            int w = 0;

            for (int i = 0; i < height; i++)
            {   
                w = 0;
                for (int k = 0; k < baselen; k++)
                {
                    if(var.map[i][k] == '1')
                        mlx_put_image_to_window(var.mlx, var.win, var.wall, w, h); // 이미지를 화면으로 쏘는 것
                    if(var.map[i][k] == '0')
                        mlx_put_image_to_window(var.mlx, var.win, var.tile, w, h); // 이미지를 화면으로 쏘는 것
                    if(var.map[i][k] == 'P')
                    {
                        mlx_put_image_to_window(var.mlx, var.win, var.player, w, h); // 이미지를 화면으로 쏘는 것
                        var.player_x = w;
                        var.player_y = h;
                    }
                    if(var.map[i][k] == 'C')
                        mlx_put_image_to_window(var.mlx, var.win, var.collection, w, h); // 이미지를 화면으로 쏘는 것
                    if(var.map[i][k] == 'E')
                        mlx_put_image_to_window(var.mlx, var.win, var.goal, w, h); // 이미지를 화면으로 쏘는 것
                    w += BLOCK;
                }
                h += BLOCK;
            }
            mlx_hook(var.win,2,1L<<0, key_press, &var);
            mlx_hook(var.win, 17, 0, t, &var);
            mlx_loop(var.mlx);
        }
        else
            printf("invalid map\n");
    }
    else
        printf("input Err\n");
}

