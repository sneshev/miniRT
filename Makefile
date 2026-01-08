# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/03 17:28:55 by mmisumi           #+#    #+#              #
#    Updated: 2026/01/08 08:20:53 by stefuntu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT
SRCS:= src/main.c
OBJS := $(patsubst src/%.c, .obj/%.o, $(SRCS))

LIBFT := libft/libft.a
CC := cc -Wall -Werror -Wextra -g -Iincludes -Ilibft -Imlx_linux -O3
RM := rm -rf


all: minilibx $(LIBFT) .obj $(NAME)

.obj:
	mkdir -p .obj

$(LIBFT):
	make -C libft

minilibx:
	@[ -f "mlx_linux/libmlx.a" ] || (cd mlx_linux && make)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -Llibft -lft -Lmlx_linux -lmlx -lXext -lX11 -lm -lz -o $(NAME)

.obj/%.o: src/%.c
	$(CC) -c $< -o $@

clean:
	$(RM) .obj
	make -C libft clean
# 	make -C mlx_linux clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re