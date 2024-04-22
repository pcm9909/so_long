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


// //for mac
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
    void    *player_front;
    void    *player_back;
    void    *player_right;
    void    *player_left;
    void    *goal;
    void    *goal1; 
	int		img_width;
	int		img_height;
    char    **map;
    char    **dfs_maps;
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
    int     step;
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
    free(ptr);
    return (new_ptr);
}

int key_press(int keycode, t_vars *p)
{
    mlx_put_image_to_window(p->mlx, p->win, p->wall, 0, 0);
    
    if (p->cntC > 0)
        p->map[p->exit_y / BLOCK][p->exit_x / BLOCK] = '1';
    if (keycode == UP_W)
    {
        if(p->map[p->player_y / BLOCK - 1][p->player_x / BLOCK] != '1')
        {
            mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
            p->player_y -= BLOCK;
            mlx_put_image_to_window(p->mlx, p->win, p->player_back, p->player_x, p->player_y);
            p->move++;
        }
    }
    if (keycode == DOWN_S)
    {
        if (p->map[p->player_y / BLOCK + 1][p->player_x / BLOCK] != '1')
        {
            mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
            p->player_y += BLOCK;
            mlx_put_image_to_window(p->mlx, p->win, p->player_front, p->player_x, p->player_y);
            p->move++;
        }
    }
    else if (keycode == LEFT_A)
    {
        if(p->map[p->player_y / BLOCK][p->player_x / BLOCK - 1] != '1')
        {
            mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
            p->player_x -= BLOCK;
            mlx_put_image_to_window(p->mlx, p->win, p->player_left, p->player_x, p->player_y);
            p->move++; 
        }
    }
    else if (keycode == RIGHT_D)
    {   
        if(p->map[p->player_y / BLOCK][p->player_x / BLOCK + 1] != '1')
        {
            mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
            p->player_x += BLOCK;
            mlx_put_image_to_window(p->mlx, p->win, p->player_right, p->player_x, p->player_y);
            p->move++;
        }
    }
    else if (keycode == EXIT_ESC)
        exit(0);
    char *pp;
    pp =ft_itoa(p->move);
    mlx_string_put(p->mlx, p->win,10,20, 0xFFFFFF,pp);
    free(pp);
    if(p->map[p->player_y / BLOCK][p->player_x / BLOCK] == 'C')
    {
        p->cntC--;
        p->map[p->player_y / BLOCK][p->player_x / BLOCK] = '0';
    }
    if (p->cntC == 0)
    {
        p->map[p->exit_y / BLOCK][p->exit_x / BLOCK] = 'E';
        mlx_put_image_to_window(p->mlx, p->win, p->goal1, p->exit_x, p->exit_y);
    }
    if(p->cntC == 0 && p->map[p->player_y / BLOCK][p->player_x / BLOCK] == 'E')
        exit(0);
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



char **make_dfs_map(t_vars p)
{
    int i;
    char **dfs_maps;

    i = 0;
    dfs_maps = (char **)malloc(sizeof(char *) * (p.height + 1));
    while (i < p.height)
    {
        dfs_maps[i] = malloc(p.baselen + 1);
        ft_memcpy(dfs_maps[i], p.map[i], p.baselen + 1);
        i++;
    }
    dfs_maps[i] = NULL;
    return (dfs_maps);
}

int dfs(char **map, int x, int y, char find)
{
    int cnt;

    cnt = 0;
    if(find == 'C')
    {
        if (map[y][x] == '1' || map[y][x] == 'E')
            return 0;
    }
    else
    {
        if (map[y][x] == '1')
            return 0;
    }
    if(map[y][x] != '1')
    {
        if (map[y][x] == find)
            cnt++;
        map[y][x] = '1';
        cnt += dfs(map, x - 1, y, find);
        cnt += dfs(map, x, y + 1, find);
        cnt += dfs(map, x + 1, y, find);
        cnt += dfs(map, x, y - 1, find);
        return cnt;
    }
    return 0;
}

int main(int argc, char **argv)
{
    int fd;
    char *line;
    char **tmp;
    t_vars  var;
    var.height = 0;
    var.move = 0; 

    if (argc == 2)
    {
        if (ft_strncmp(ft_strchr(argv[1], '.'), ".ber\0", 5) == 0)
        {
            fd = open(argv[1], O_RDONLY);
            if (fd == -1) 
                exit_error("File does not exist\n");
            var.map = (char **)malloc(sizeof(char *));
            while ((line = get_next_line(fd)) > 0)
            {
                var.map[var.height] = ft_strdup(line);
                free(line);
                var.height++;
                var.map = (char **)ft_realloc(var.map, (var.height + 1) * sizeof(char *));
            }
            var.map[var.height] = NULL;
            // map이 제대로 적성되었는지 검증 1. x축이 잘 들어왔는가? map이 3줄 이상인가
            if (var.height < 3)
                exit_error("The map is not valid\n");
            var.baselen = ft_strlen(var.map[0]);
            int j = 1;
            while (j < var.height)
            {
                if (var.baselen != ft_strlen(var.map[j]))
                    exit_error("The map is not valid\n");
                j++;
            }
            // map이 제대로 적성되었는지 검증 2. y축이 잘 들어왔는가? map이 3줄 이상인가
            int i = 0;
            while (i < var.baselen)
            {
                if (var.map[0][i] != '1' || var.map[var.height - 1][i] != '1')
                    exit_error("The map is not valid\n");
                i++;
            }
            //check 테두리
            i = 0;
            while (i < var.height)
            {
                if (var.map[i][0] != '1' || var.map[i][var.baselen - 1] != '1')
                    exit_error("The map is not valid\n");
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
                        exit_error("The map is not valid\n");
                    j++;
                }
                i++;
            }
            if (var.cntC < 1 || cntP != 1 || cntE != 1)
                exit_error("The map is not valid\n");

            var.mlx = mlx_init();
            var.win = mlx_new_window(var.mlx, var.baselen * BLOCK, var.height * BLOCK, "img test");
            var.wall = mlx_xpm_file_to_image(var.mlx, "./img/wall.xpm", & var.img_width, &var.img_height);
            var.tile = mlx_xpm_file_to_image(var.mlx, "./img/tile.xpm", &var.img_width, &var.img_height);
            var.player_front = mlx_xpm_file_to_image(var.mlx, "./img/player_front.xpm", &var.img_width, &var.img_height);
            var.player_back = mlx_xpm_file_to_image(var.mlx, "./img/player_back.xpm", &var.img_width, &var.img_height);
            var.player_right = mlx_xpm_file_to_image(var.mlx, "./img/player_right.xpm", &var.img_width, &var.img_height);
            var.player_left = mlx_xpm_file_to_image(var.mlx, "./img/player_left.xpm", &var.img_width, &var.img_height);
            var.collection = mlx_xpm_file_to_image(var.mlx, "./img/collection.xpm", &var.img_width, &var.img_height);
            var.goal = mlx_xpm_file_to_image(var.mlx, "./img/exit.xpm", &var.img_width, &var.img_height);
            var.goal1 = mlx_xpm_file_to_image(var.mlx, "./img/exit1.xpm", &var.img_width, &var.img_height);
            
            var.h = 0;
            for (int i = 0; i < var.height; i++)
            {   
                var.w = 0;
                for (int k = 0; k < var.baselen; k++)
                {
                    if(var.map[i][k] == '1')
                        mlx_put_image_to_window(var.mlx, var.win, var.wall, var.w, var.h); 
                    if(var.map[i][k] == '0')
                        mlx_put_image_to_window(var.mlx, var.win, var.tile, var.w, var.h); 
                    if(var.map[i][k] == 'P')
                    {
                        var.player_x = var.w;
                        var.player_y = var.h;
                        mlx_put_image_to_window(var.mlx, var.win, var.player_front, var.w, var.h);
                    }
                    if(var.map[i][k] == 'C')
                        mlx_put_image_to_window(var.mlx, var.win, var.collection, var.w, var.h);
                    if(var.map[i][k] == 'E')
                    {
                        var.exit_x = var.w;
                        var.exit_y = var.h;
                        mlx_put_image_to_window(var.mlx, var.win, var.goal, var.w, var.h);
                    }
                    var.w += BLOCK;
                }
                var.h += BLOCK;
            }
            char **map1;
            char **map2;
            int a;
            int b;
            map1 = make_dfs_map(var);
            map2 = make_dfs_map(var);
            printf("%c\n", var.map[var.player_y / BLOCK][var.player_x / BLOCK]);
            a = dfs(map1, var.player_x / BLOCK, var.player_y / BLOCK, 'E');
            b = dfs(map2, var.player_x / BLOCK, var.player_y / BLOCK, 'C');
            printf("E = %d dfs = %d\n", cntE ,a);
            printf("C = %d dfs = %d\n",var.cntC ,b);
            mlx_hook(var.win,2,1L<<0, key_press, &var);
            mlx_hook(var.win, 17, 0, t, &var);
            mlx_loop(var.mlx);
        }
        else
            exit_error("Please enter the [.ber] file\n");
    }
    else
        exit_error("The number of inputs is not correct\n");
}