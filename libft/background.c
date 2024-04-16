#include "./mlx/mlx.h"

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



int main()
{
    t_vars  var;
    t_data  img;

    img.relative_path = "./a.xpm";
    var.mlx = mlx_init();
    var.win = mlx_new_window(var.mlx, 1920, 1080, "img test");
    img.img = mlx_xpm_file_to_image(var.mlx, img.relative_path, &img.img_width, &img.img_height);
    mlx_put_image_to_window(var.mlx, var.win, img.img, 30, 30); // 이미지를 화면으로 쏘는 것 

    mlx_loop(var.mlx);
}