# So_long
minilib를 활용해 2D 게임을 구현하는 프로젝트 
## 컴파일
<https://projects.intra.42.fr/projects/so_long>

1. 위 사이트에서 OS에 맞게 minilibx를 다운 후 상위 폴더로 경로 이동
2. 폴더명을 mlx로 변경
3. mlx폴더에서 먼저 make후 컴파일


ubuntu
```shell
make
```
m1
Makefile에 all 부분 수정 필요 

-Lmlx -lmlx -lXext -lX11 <- 이부분을 아래와 같이 변경 후 컴파일 

-I. -Lmlx -lmlx -framework OpenGL -framework Appkit
