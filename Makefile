# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chunpark <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 14:40:08 by chunpark          #+#    #+#              #
#    Updated: 2024/04/26 14:40:10 by chunpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = so_long
DIR = ./mandatory
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

BONUS = so_long_bonus
BNS_DIR = ./bonus
BNS_SRC = 	so_long_bonus.c \
			draw_map_1_bonus.c \
			draw_map_2_bonus.c \
			key_press_handler_bonus.c \
			load_image_bonus.c \
			load_map_bonus.c \
			map_verification_bonus.c \
			player_movement_bonus.c \
			map_validation_bonus.c
BNS_SRCS = $(addprefix $(BNS_DIR)/, $(BNS_SRC))
BNS_OBJS = $(BNS_SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@echo "메이크 올"
	@make -C ./mlx > /dev/null
	@echo "메이크 엠엘엑스"
	@make re -C ./utils/libft > /dev/null
	@echo "메이크 엘아이비에프티"
	@make re -C ./utils/get_next_line > /dev/null
	@echo "메이크 겟넥스트라인"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./utils/libft/libft.a ./utils/get_next_line/get_next_line.a -Lmlx -lmlx -lXext -lX11
	@echo "메이크 쏘롱"
	@sleep 0.5

bonus: $(BONUS)

$(BONUS): $(BNS_OBJS)
	@echo "메이크 보너스"
	@make -C ./mlx > /dev/null
	@echo "메이크 엠엘엑스"
	@make re -C ./utils/libft > /dev/null
	@echo "메이크 엘아이비에프티"
	@make re -C ./utils/get_next_line > /dev/null
	@echo "메이크 겟넥스트라인"
	@$(CC) $(CFLAGS) -o $(BONUS) $(BNS_OBJS) ./utils/libft/libft.a ./utils/get_next_line/get_next_line.a -Lmlx -lmlx -lXext -lX11
	@echo "메이크 쏘롱보너스"
	@sleep 0.5

clean:
	@echo "클린"
	@make clean -C ./utils/libft  > /dev/null
	@echo "클린 엘아이비에프티"
	@make clean -C ./utils/get_next_line  > /dev/null
	@echo "클린 겟넥스트라인"
	@rm -f $(OBJS) $(BNS_OBJS)
	@echo "클린 쏘롱"
	@sleep 0.5

fclean: clean
	@echo "에프클린"
	@make fclean -C ./utils/libft > /dev/null
	@echo "에프클린 엘아이비에프티"
	@make fclean -C ./utils/get_next_line > /dev/null
	@echo "에프클린 겟넥스트라인"
	@rm -f $(NAME) $(BONUS)
	@echo "에프클린 쏘롱"
	@sleep 0.5

re: fclean all

re_bonus: fclean bonus

dance:
			@sleep 0.5
			@clear
			@echo "\033[35m♪┏(・o･)┛♪\033[0m"
			@sleep 0.5
			@clear
			@echo "\033[1;33m♪┗(・o･)┓♪\033[0m"
			@sleep 0.5
			@clear
			@echo "\033[35m♪┏(・o･)┛♪\033[0m"
			@sleep 0.5
			@clear
			@echo "\033[1;33m♪┗(・o･)┓♪\033[0m"
			@sleep 0.5
			@clear


.PHONY: all bonus clean fclean re re_bonus dance
