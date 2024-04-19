#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include "./mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define BLOCK 64


//for linux
# define UP_W				119
# define DOWN_S				115
# define LEFT_A				97
# define RIGHT_D			100
# define EXIT_ESC			65307
# define EXIT_BUTTON		17


//for mac
// #define UP_W 13
// #define DOWN_S 1
// #define LEFT_A 0
// #define RIGHT_D 2
// #define EXIT_ESC 53
// #define EXIT_BUTTON 17

typedef struct s_vars
{
    void    *mlx;
    void    *win;
    void	*wall;
    void    *tile;
    void    *collection;
    void    *player;
    void    *goal;
    void    *goal1; 
	int		img_width;
	int		img_height;
    char    **map;
    int     player_x;
    int     player_y;
    int     exit_x;
    int     exit_y;
    int     baselen;
    int     height;
    int     h;
    int     w;
    int     cntC;
    int     move;
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
    mlx_put_image_to_window(p->mlx, p->win, p->wall, 0, 0);
    mlx_string_put(p->mlx, p->win,10,20, 0xFFFFFF,ft_itoa(p->move));
    if (p->cntC > 0)
        p->map[p->exit_y / BLOCK][p->exit_x / BLOCK] = '1';

    if (keycode == UP_W)
    {
        if(p->map[p->player_y / BLOCK - 1][p->player_x / BLOCK] != '1')
        {
            mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
            p->player_y -= BLOCK;
            mlx_put_image_to_window(p->mlx, p->win, p->player, p->player_x, p->player_y);
            p->move++;
            
        }
    }
    if (keycode == DOWN_S)
    {
        if (p->map[p->player_y / BLOCK + 1][p->player_x / BLOCK] != '1')
        {
            mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
            p->player_y += BLOCK;
            mlx_put_image_to_window(p->mlx, p->win, p->player, p->player_x, p->player_y);
            p->move++;
           
        }
    }
    else if (keycode == LEFT_A)
    {
        if(p->map[p->player_y / BLOCK][p->player_x / BLOCK - 1] != '1')
        {
            mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
            p->player_x -= BLOCK;
            mlx_put_image_to_window(p->mlx, p->win, p->player, p->player_x, p->player_y);
            p->move++;
            
        }
    }
    else if (keycode == RIGHT_D)
    {   
        if(p->map[p->player_y / BLOCK][p->player_x / BLOCK + 1] != '1')
        {
            mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
            p->player_x += BLOCK;
            mlx_put_image_to_window(p->mlx, p->win, p->player, p->player_x, p->player_y);
            p->move++;
            
        }
    }
    else if (keycode == EXIT_ESC)
        exit(0);
    if(p->map[p->player_y / BLOCK][p->player_x / BLOCK] == 'C')
    {
        p->cntC--;
        printf("cntC = %d\n", p->cntC);
        p->map[p->player_y / BLOCK][p->player_x / BLOCK] = '0';
    }
    if (p->cntC == 0)
    {
        p->map[p->exit_y / BLOCK][p->exit_x / BLOCK] = 'E';
        mlx_put_image_to_window(p->mlx, p->win, p->goal1, p->exit_x, p->exit_y);
    }
    if(p->cntC == 0 && p->map[p->player_y / BLOCK][p->player_x / BLOCK] == 'E')
        exit(0);
    printf("px: %d py : %d\n", p->player_x, p->player_y);
    printf("x : %d y : %d\n",p->player_x / BLOCK, p->player_y / BLOCK);
    printf("map : %c\n", p->map[p->player_y / BLOCK][p->player_x / BLOCK]);
    return (0);
}

int    t()
{
   exit(0);
}

void    exit_error(char *str)
{
    ft_putstr_fd(str,1);
    exit(1);
}

int main(int argc, char **argv)
{
    int fd;
    char *line;
    t_vars  var;
    var.height = 0;
    var.move = 0; 

    if (argc == 2)
    {
        if (ft_strncmp(ft_strchr(argv[1], '.'), ".ber", 4) == 0) // .ber파일인지 검증
        {
            fd = open(argv[1], O_RDONLY);
            if (fd == -1) 
                exit_error("File does not exist\n");
            var.map = (char **)malloc(sizeof(char *));
            while ((line = get_next_line(fd)) > 0) //.ber파일을 이중배열로 만듬
            {
                var.map[var.height] = ft_strdup(line);
                free(line);
                var.height++;
                var.map = (char **)ft_realloc(var.map, (var.height + 1) * sizeof(char *));
            }
            // map이 제대로 적성되었는지 검증 1. x축이 잘 들어왔는가? map이 3줄 이상인가
            if (var.height < 3)
                printf("The map is not valid\n");
            var.baselen = ft_strlen(var.map[0]) - 1;
            int j = 1;
            printf("%d %d\n", var.height, var.baselen);
            while (j < var.height)
            {
                printf("%d\n", ft_strlen(var.map[j]) - 1);
                if (var.baselen != ft_strlen(var.map[j]) - 1)
                {
                    printf("%d",j);
                    if (j == var.height - 1)
                    {
                        printf("last in\n");
                        printf("%d %d \n", var.baselen, ft_strlen(var.map[j]));
                        if (var.baselen == ft_strlen(var.map[j]))
                            break;
                    }
                    exit_error("The map is not valid\n");
                    break;
                }
                j++;
            }
            // map이 제대로 적성되었는지 검증 2. y축이 잘 들어왔는가? map이 3줄 이상인가
            int i = 0;
            while (i < var.baselen)
            {
                if (var.map[0][i] != '1' || var.map[var.height - 1][i] != '1')
                {
                    exit_error("The map is not valid\n");
                    break;
                }
                i++;
            }
            //check 테두리
            i = 0;
            while (i < var.height)
            {
                if (var.map[i][0] != '1' || var.map[i][var.baselen - 1] != '1')
                {
                    exit_error("The map is not valid\n");
                    break;
                }
                i++;
            }
            var.cntC = 0;
            int cntP = 0;
            int cntE = 0;
            i = 1;
            while (i < var.height - 1)
            {
                int j = 1;
                while (j < var.baselen - 1)
                {
                    if (var.map[i][j] == 'C')
                        var.cntC++;
                    else if (var.map[i][j] == 'P')
                        cntP++;
                    else if (var.map[i][j] == 'E')
                        cntE++;
                    else if (var.map[i][j] != '1' && var.map[i][j] != '0')
                    {
                        printf("The map is not valid\n");
                        return 0;
                    }
                    j++;
                }
                i++;
            }
            printf("C=%d P=%d E=%d\n", var.cntC, cntP, cntE);
            if (var.cntC < 1 || cntP != 1 || cntE != 1)
            {
                exit_error("The map is not valid\n");
                return (0);
            }
            var.mlx = mlx_init();
            var.win = mlx_new_window(var.mlx, var.baselen * BLOCK, var.height * BLOCK, "img test");
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
            //E1
            var.goal1 = mlx_xpm_file_to_image(var.mlx, "./img/exit1.xpm", &var.img_width, &var.img_height);
            var.h = 0;
            for (int i = 0; i < var.height; i++)
            {   
                var.w = 0;
                for (int k = 0; k < var.baselen; k++)
                {
                    if(var.map[i][k] == '1')
                        mlx_put_image_to_window(var.mlx, var.win, var.wall, var.w, var.h); // 이미지를 화면으로 쏘는 것
                    if(var.map[i][k] == '0')
                        mlx_put_image_to_window(var.mlx, var.win, var.tile, var.w, var.h); // 이미지를 화면으로 쏘는 것
                    if(var.map[i][k] == 'P')
                    {
                        var.player_x = var.w;
                        var.player_y = var.h;
                        mlx_put_image_to_window(var.mlx, var.win, var.player, var.w, var.h); // 이미지를 화면으로 쏘는 것
                    }
                    if(var.map[i][k] == 'C')
                        mlx_put_image_to_window(var.mlx, var.win, var.collection, var.w, var.h); // 이미지를 화면으로 쏘는 것
                    if(var.map[i][k] == 'E')
                    {
                        var.exit_x = var.w;
                        var.exit_y = var.h;
                        mlx_put_image_to_window(var.mlx, var.win, var.goal, var.w, var.h); // 이미지를 화면으로 쏘는 것
                    }
                    var.w += BLOCK;
                }
                var.h += BLOCK;
            }
            printf("%d %d\n", var.w, var.h);
            mlx_hook(var.win,2,1L<<0, key_press, &var);
            mlx_hook(var.win, 17, 0, t, &var);
            mlx_loop(var.mlx);
        }
        else
            exit_error("The map is not valid\n");
    }
    else
        exit_error("The number of inputs is not correct\n");
}

