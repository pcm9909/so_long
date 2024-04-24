all:
	@make re -C ./libft
	@make re -C ./get_next_line
	gcc *.c ./libft/libft.a ./get_next_line/get_next_line.a -Lmlx -lmlx -lXext -lX11 -g -fsanitize=address