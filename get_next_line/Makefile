# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/08 03:15:48 by chunpark          #+#    #+#              #
#    Updated: 2024/04/09 19:17:42 by chunpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADR = get_next_line.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = get_next_line.a
SRCS =	get_next_line.c \
		get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADR)
			@ar rcs $(NAME) $(OBJS)

%.o: %.c
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -f $(OBJS)

fclean: clean
			@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
