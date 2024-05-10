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
```
Makefile에 all 부분 수정 필요 
-Lmlx -lmlx -lXext -lX11 <- 이부분을 아래와 같이 변경 후 컴파일 
-I. -Lmlx -lmlx -framework OpenGL -framework Appkit

make
```

## 맵 만들기 규칙
1. 파일명이 .ber로 끝날 것
2. C 1개 이상, P 1개, E 1개 꼭 필요
3. 1로 둘러 쌓여 있고 맵의 크기가 사각형이어야 함 
4. 유효한 경로를 가질 것 (P가 C를 모두 획득할 수 있어야 하고 E까지 도달 가능해야 함)

예시
```c
1111111
1000001
1C00C11
10E0001
10000P1
1111111
```
