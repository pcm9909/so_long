#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include "./mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define BLOCK 64

# define UP_W				119
# define DOWN_S				115
# define LEFT_A				97
# define RIGHT_D			100
# define EXIT_ESC			65307
# define EXIT_BUTTON		17

typedef struct s_data
{
    void	*img;
	char	*relative_path;
	int		img_width;
	int		img_height;
}               t_data;

typedef struct s_vars
{
    void    *mlx;
    void    *win;
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

int	key_press(int keycode, t_data *p)
{
	if (keycode == UP_W && p->play_y != 0)
		p->play_y -= p->img_y;
	if (keycode == DOWN_S && p->play_y != 700)
		p->play_y += p->img_y;
	else if (keycode == LEFT_A && p->play_x != 0)
		p->play_x -= p->img_x;
	else if (keycode == RIGHT_D && p->play_x != 900)
		p->play_x += p->img_x;
	else if (keycode == EXIT_ESC)
		exit(0);
	else if (keycode == EXIT_BUTTON)
		exit(0);
	printf("x: %d y : %d\n", p->play_x, p->play_y);
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
    char **map;
    t_data  wall; // 1
    t_data  tile; // 0
    t_data  collection; // C
    t_data  player; // P
    t_data  exit; // E
    
    t_vars  var;

    if (argc == 2)
    {
        if (ft_strncmp(ft_strchr(argv[1], '.'), ".ber", 4) == 0) // .ber파일인지 검증
        {
            fd = open(argv[1], O_RDONLY);
            map = (char **)malloc(sizeof(char *));
            while ((line = get_next_line(fd)) > 0) //.ber파일을 이중배열로 만듬
            {
                map[height] = ft_strdup(line);
                free(line);
                height++;
                map = (char **)ft_realloc(map, (height + 1) * sizeof(char *));
            }
            // map이 제대로 적성되었는지 검증 1. x축이 잘 들어왔는가? map이 3줄 이상인가
            if (height < 3)
                printf("error height\n");
            int baselen = ft_strlen(map[0]) - 1;
            int j = 1;
            printf("%d %d\n", height, baselen);
            while (j < height)
            {
                printf("%d\n", ft_strlen(map[j]) - 1);
                if (baselen != ft_strlen(map[j]) - 1)
                {
                    if (j == height - 1)
                    {
                        if (baselen == ft_strlen(map[j]))
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
                if (map[0][i] != '1' || map[height - 1][i] != '1')
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
                if (map[i][0] != '1' || map[i][baselen - 1] != '1')
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
                    if (map[i][j] == 'C')
                        cntC++;
                    else if (map[i][j] == 'P')
                        cntP++;
                    else if (map[i][j] == 'E')
                        cntE++;
                    else if (map[i][j] != '1' && map[i][j] != '0')
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
            wall.relative_path = "./img/wall.xpm";
            exit.relative_path = "./img/exit.xpm";
            tile.relative_path = "./img/tile.xpm";
            player.relative_path = "./img/player.xpm";
            collection.relative_path = "./img/collection.xpm";
            var.mlx = mlx_init();
            var.win = mlx_new_window(var.mlx, baselen * BLOCK, height * BLOCK, "img test");
            //1
            wall.img = mlx_xpm_file_to_image(var.mlx, wall.relative_path, &wall.img_width, &wall.img_height);
            //0
            tile.img = mlx_xpm_file_to_image(var.mlx, tile.relative_path, &tile.img_width, &tile.img_height);
            //P
            player.img = mlx_xpm_file_to_image(var.mlx, player.relative_path, &player.img_width, &player.img_height);
            //C
            collection.img = mlx_xpm_file_to_image(var.mlx, collection.relative_path, &collection.img_width, &collection.img_height);
            //E
            exit.img = mlx_xpm_file_to_image(var.mlx, exit.relative_path, &exit.img_width, &exit.img_height);
            int h = 0;
            int w = 0;
            for (int i = 0; i < height; i++)
            {   
                w = 0;
                for (int k = 0; k < baselen; k++)
                {
                    if(map[i][k] == '1')
                        mlx_put_image_to_window(var.mlx, var.win, wall.img, w, h); // 이미지를 화면으로 쏘는 것
                    if(map[i][k] == '0')
                        mlx_put_image_to_window(var.mlx, var.win, tile.img, w, h); // 이미지를 화면으로 쏘는 것
                    if(map[i][k] == 'P')
                        mlx_put_image_to_window(var.mlx, var.win, player.img, w, h); // 이미지를 화면으로 쏘는 것
                    if(map[i][k] == 'C')
                        mlx_put_image_to_window(var.mlx, var.win, collection.img, w, h); // 이미지를 화면으로 쏘는 것
                    if(map[i][k] == 'E')
                        mlx_put_image_to_window(var.mlx, var.win, exit.img, w, h); // 이미지를 화면으로 쏘는 것
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

