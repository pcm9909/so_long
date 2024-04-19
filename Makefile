all:
	@make re -C ./libft
	@make re -C ./get_next_line
	gcc main.c ./libft/libft.a ./get_next_line/get_next_line.a -Lmlx -lmlx -lXext -lX11