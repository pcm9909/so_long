#include "./mlx/mlx.h"


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

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
    void    *mlx;
    void    *mlx_win;
    t_data  img;

    mlx = mlx_init();
    //mlx_new_image(void *mlx_ptr, int width, int height)
    // mlx_ptr = init된 ptr
    // width = 생성할 img의 넓이
    // height = 생성할 img의 높이 
    img.img = mlx_new_image(mlx, 1080, 720);
    // mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title)
    // mlx_ptr = init된 ptr
    // size_x = 가로 크기 
    // size_y = 세로 크기
    // title = 상단바에 출력될 문자
    mlx_win = mlx_new_window(mlx, 1080, 720, "so_long");
    // mlx_loop(void *mlx_ptr)
    // 입력을 수신받고 반환하는 함수

    //mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian)
    //img_ptr = 사용할 이미지 
    //bits_per_pixel = 픽셀의 색상을 표현하는데 필요한 비트의 수 
    //size_line = 메모리 안에서 이미지 한 줄을 저장하는데 필요한 바이트 수
    //endian = 이미지의 픽셀 색상을 little(0) 또는 big에 저장해야하는지 여부 (big endian, little endian)
    //https://ko.wikipedia.org/wiki/%EC%97%94%EB%94%94%EC%96%B8
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    draw_rectangle(&img, 100, 100, 200, 150, 0xFFFF0000); // (100, 100)에서 시작하여 너비가 200이고 높이가 150인 빨간색 사각형 그리기

    my_mlx_pixel_put(&img, 5, 5, 0xFFFF0000);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    
    mlx_loop(mlx);
}
