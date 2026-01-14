# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/03 17:28:55 by mmisumi           #+#    #+#              #
#    Updated: 2026/01/14 18:07:18 by winnitytrin      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT
SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, .obj/%.o, $(SRCS))

# MLX_FLAGS	:= -Lmlx_linux -lmlx -lXext -lX11 -lz
# MLX_DIR		:= mlx_linux
# MLX_INC		:= -Imlx_linux

LIBFT := libft/libft.a
CC := cc -Wall -Werror -Wextra -g -Iincludes -O0
# $(MLX_INC)

RM := rm -rf

all: $(LIBFT) .obj $(NAME)
# minilibx

.obj:
	mkdir -p .obj

$(LIBFT):
	make -C libft

# minilibx:
# 	@[ -f "$(MLX_DIR)/libmlx.a" ] || (cd $(MLX_DIR) && make)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -Llibft -lm -lft -o $(NAME)
#  $(MLX_FLAGS)

.obj/%.o: src/%.c
	$(CC) -c $< -o $@

clean:
	$(RM) .obj
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
# minilibx