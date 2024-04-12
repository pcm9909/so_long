#include "./mlx/mlx.h"
#include <stdio.h>


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars 
{
    void    *mlx;
    void    *win;
}           t_vars;



void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}



void draw_rectangle(t_data *data, int x, int y, int width, int height, int color) {
    int i, j;
    for (i = x; i < x + width; i++) {
        for (j = y; j < y + height; j++) {
            my_mlx_pixel_put(data, i, j, color);
        }
    }
}

int main()
{
    t_vars  vars;
    t_data  img;

    vars.mlx = mlx_init();
    //mlx_new_image(void *mlx_ptr, int width, int height)
    // mlx_ptr = init된 ptr
    // width = 생성할 img의 넓이
    // height = 생성할 img의 높이 
    img.img = mlx_new_image(vars.mlx, 2000, 2000); // 지정한 크기를 넘어선 값을 put하면 세그폴트가 발생한다. 
    // mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title)
    // mlx_ptr = init된 ptr
    // size_x = 가로 크기 
    // size_y = 세로 크기
    // title = 상단바에 출력될 문자
    vars.win = mlx_new_window(vars.mlx, 2000, 2000, "so_long");
    // mlx_loop(void *mlx_ptr)
    // 입력을 수신받고 반환하는 함수

    //mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian)
    //img_ptr = 사용할 이미지 
    //bits_per_pixel = 픽셀의 색상을 표현하는데 필요한 비트의 수 
    //size_line = 메모리 안에서 이미지 한 줄을 저장하는데 필요한 바이트 수
    //endian = 이미지의 픽셀 색상을 little(0) 또는 big에 저장해야하는지 여부 (big endian, little endian)
    //https://ko.wikipedia.org/wiki/%EC%97%94%EB%94%94%EC%96%B8
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    // 1층
    draw_rectangle(&img, 0, 0, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 150, 0, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 300, 0, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 450, 0, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 600, 0, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 750, 0, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 900, 0, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
     // 2층
    draw_rectangle(&img, 0, 150, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 150, 150, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 300, 150, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 450, 150, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 600, 150, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 750, 150, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 900, 150, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
     // 3층
    draw_rectangle(&img, 0, 300, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 150, 300, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 300, 300, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 450, 300, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 600, 300, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 750, 300, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 900, 300, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    // 4층
    draw_rectangle(&img, 0, 450, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 150, 450, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 300, 450, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 450, 450, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 600, 450, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 750, 450, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 900, 450, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    // 5층
    draw_rectangle(&img, 0, 600, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 150, 600, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 300, 600, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 450, 600, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 600, 600, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 750, 600, 150, 150, 0x00000000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기
    draw_rectangle(&img, 900, 600, 150, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기

    my_mlx_pixel_put(&img, 5, 5, 0xFFFF0000); // 픽셀 하나를 찍는 것 
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0); // 이미지를 화면으로 쏘는 것 
    mlx_string_put(vars.mlx, vars.win,100,100,0xFFFFFFFFF, "hi");
    //mlx_key_hook(vars.win, close, &vars); 
    //int mlx_key_hook(t_win_list *win,int (*funct)(),void *param)
    mlx_loop(vars.mlx);
}
