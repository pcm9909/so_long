CC = cc
#CFLAGS = -Wall -Wextra -Werror

NAME = so_long
DIR = ./srcs
SRC = 	so_long.c \
		draw_map_1.c \
		draw_map_2.c \
		key_press_handler.c \
		load_image.c \
		load_map.c \
		map_verification.c \
		player_movement.c \
		map_validation.c
SRCS = $(addprefix $(DIR)/, $(SRC))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@make -C ./mlx
	@make re -C ./utils/libft
	@make re -C ./utils/get_next_line
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./utils/libft/libft.a ./utils/get_next_line/get_next_line.a -I. -Lmlx -lmlx -framework OpenGL -framework Appkit
clean:
	@make clean -C ./utils/libft
	@make clean -C ./utils/get_next_line
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C ./utils/libft
	@make fclean -C ./utils/get_next_line
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

	

# all:
# 	@make re -C ./libft
# 	@make re -C ./get_next_line
# 	gcc *.c ./libft/libft.a ./get_next_line/get_next_line.a -Lmlx -lmlx -lXext -lX11 -g -fsanitize=address
