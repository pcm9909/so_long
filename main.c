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
    void    *enemy;
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


//-------------------------------

void move_forward(t_vars *p)
{
    if(p->map[p->player_y / BLOCK - 1][p->player_x / BLOCK] != '1')
    {
        mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
        p->player_y -= BLOCK;
        mlx_put_image_to_window(p->mlx, p->win, p->player_back, p->player_x, p->player_y);
        p->move++;
    }
}

void move_backward(t_vars *p)
{
    if (p->map[p->player_y / BLOCK + 1][p->player_x / BLOCK] != '1')
    {
        mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
        p->player_y += BLOCK;
        mlx_put_image_to_window(p->mlx, p->win, p->player_front, p->player_x, p->player_y);
        p->move++;
    }
}

void move_left(t_vars *p)
{
    if(p->map[p->player_y / BLOCK][p->player_x / BLOCK - 1] != '1')
    {
        mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
        p->player_x -= BLOCK;
        mlx_put_image_to_window(p->mlx, p->win, p->player_left, p->player_x, p->player_y);
        p->move++; 
    }
}

void move_right(t_vars *p)
{   
    if(p->map[p->player_y / BLOCK][p->player_x / BLOCK + 1] != '1')
    {
        mlx_put_image_to_window(p->mlx, p->win, p->tile, p->player_x, p->player_y);
        p->player_x += BLOCK;
        mlx_put_image_to_window(p->mlx, p->win, p->player_right, p->player_x, p->player_y);
        p->move++;
    }
}

void show_cnt(t_vars *p)
{
    char *move_cnt;
    
    move_cnt = ft_itoa(p->move);
    mlx_string_put(p->mlx, p->win,10,20, 0xFFFFFF,move_cnt);
    free(move_cnt);
}

void handle_exit(t_vars *p)
{
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
    if(p->map[p->player_y / BLOCK][p->player_x / BLOCK] == 'I')
        exit(0);
    if(p->cntC == 0 && p->map[p->player_y / BLOCK][p->player_x / BLOCK] == 'E')
        exit(0);
}

int key_press(int keycode, t_vars *p)
{
    mlx_put_image_to_window(p->mlx, p->win, p->wall, 0, 0);
    
    if (p->cntC > 0)
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
    show_cnt(p);
    handle_exit(p);
    return (0);
}

//-------------------------------


int    t()
{
   exit(0);
}

void    exit_error(char *str)
{
    ft_putstr_fd(str,1);
    exit(1);
}



//-----------------------------------------------------

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
void    read_map(t_vars *p, char *filename)
{
    int fd;
    char *line;

    p->height = 0;
    fd = open(filename, O_RDONLY);
    if (fd == -1) 
        exit_error("File does not exist\n");
    p-> map = (char **)malloc(sizeof(char *));
    while ((line = get_next_line(fd)) > 0)
    {
        p->map[p->height] = ft_strdup(line);
        free(line);
        p->height++;
        p->map = (char **)ft_realloc(p->map, (p->height + 1) * sizeof(char *));
    }
    p->map[p->height] = NULL;
}

void check_map_x(t_vars *var)
{
    if (var->height < 3)
        exit_error("The map is not valid\n");
    
    var->baselen = ft_strlen(var->map[0]);
    int j = 1;
    while (j < var->height)
    {
        if (var->baselen != ft_strlen(var->map[j]))
            exit_error("The map is not valid\n");
        j++;
    }
}

void check_map_y(t_vars *var)
{
    int i;
    
    i = 0;
    while (i < var->baselen)
    {
        if (var->map[0][i] != '1' || var->map[var->height - 1][i] != '1')
            exit_error("The map is not valid\n");
        i++;
    }
}

void check_map_border(t_vars *var)
{
    int i;
    
    i = 0;
    while (i < var->height)
    {
        if (var->map[i][0] != '1' || var->map[i][var->baselen - 1] != '1')
            exit_error("The map is not valid\n");
        i++;
    }
}

void check_map_input_val(t_vars *var)
{
    int cntP;
    int cntE;
    int i;
    int j;
    
    cntE = 0;
    cntP = 0;
    var->cntC = 0;
    i = 1;
    while (i < var->height - 1)
    {
        j = 1;
        while (j < var->baselen - 1)
        {
            if (var->map[i][j] == 'C')
                var->cntC++;
            else if (var->map[i][j] == 'P')
                cntP++;
            else if (var->map[i][j] == 'E')
                cntE++;
            else if (var->map[i][j] == 'I')
                ;
            else if (var->map[i][j] != '1' && var->map[i][j] != '0')
                exit_error("The map is not valid\n");
            printf("C = %d\n", var->cntC);
            j++;
        }
        i++;
    }
    if (var->cntC < 1 || cntP != 1 || cntE != 1)
        exit_error("The map is not valid\n");
}

//----------------------------------------------xpm input
char **make_dfs_map(t_vars *var)
{
    int i;
    char **dfs_maps;

    i = 0;
    dfs_maps = (char **)malloc(sizeof(char *) * (var->height + 1));
    while (i < var->height)
    {
        dfs_maps[i] = malloc(var->baselen + 1);
        ft_memcpy(dfs_maps[i], var->map[i], var->baselen + 1);
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
        if (map[y][x] == '1' || map[y][x] == 'E' || map[y][x] == 'I')
            return 0;
    }
    else
    {
        if (map[y][x] == '1' || map[y][x] == 'I')
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

void check_player_path(t_vars *var)
{
    char **map1;
    char **map2;

    map1 = make_dfs_map(var);
    map2 = make_dfs_map(var);
    if (dfs(map1, var->player_x / BLOCK, var->player_y / BLOCK, 'E') != 1)
        exit_error("The map is not valid\n");
    if (dfs(map2, var->player_x / BLOCK, var->player_y / BLOCK, 'C') != var->cntC)
        exit_error("The map is not valid\n");
}

void xpm_input(t_vars *var)
{
    var->wall = mlx_xpm_file_to_image(var->mlx, "./img/wall.xpm", & var->img_width, &var->img_height);
    var->tile = mlx_xpm_file_to_image(var->mlx, "./img/tile.xpm", &var->img_width, &var->img_height);
    var->player_front = mlx_xpm_file_to_image(var->mlx, "./img/player_front.xpm", &var->img_width, &var->img_height);
    var->player_back = mlx_xpm_file_to_image(var->mlx, "./img/player_back.xpm", &var->img_width, &var->img_height);
    var->player_right = mlx_xpm_file_to_image(var->mlx, "./img/player_right.xpm", &var->img_width, &var->img_height);
    var->player_left = mlx_xpm_file_to_image(var->mlx, "./img/player_left.xpm", &var->img_width, &var->img_height);
    var->collection = mlx_xpm_file_to_image(var->mlx, "./img/collection.xpm", &var->img_width, &var->img_height);
    var->goal = mlx_xpm_file_to_image(var->mlx, "./img/exit.xpm", &var->img_width, &var->img_height);
    var->goal1 = mlx_xpm_file_to_image(var->mlx, "./img/exit1.xpm", &var->img_width, &var->img_height);
    var->enemy = mlx_xpm_file_to_image(var->mlx, "./img/enemy.xpm", &var->img_width, &var->img_height);
}

// cntC값이 안 바뀜

int main(int argc, char **argv)
{
    int fd;
    char *line;
    char **tmp;
    t_vars  var;

    var.move = 0; 


    if (argc == 2)
    {
        if (ft_strncmp(ft_strchr(argv[1], '.'), ".ber\0", 5) == 0)
        {
            read_map(&var, argv[1]);
            check_map_x(&var);
            check_map_y(&var);
            check_map_border(&var);

            var.mlx = mlx_init();
            var.win = mlx_new_window(var.mlx, var.baselen * BLOCK, var.height * BLOCK, "img test");
            xpm_input(&var);
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
                    if(var.map[i][k] == 'I')
                        mlx_put_image_to_window(var.mlx, var.win, var.enemy, var.w, var.h);
                    var.w += BLOCK;
                }
                var.h += BLOCK;
            }
            check_player_path(&var);
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