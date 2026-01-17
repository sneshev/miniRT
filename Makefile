# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/03 17:28:55 by mmisumi           #+#    #+#              #
#    Updated: 2026/01/17 21:30:50 by winnitytrin      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

SRCS := src/main.c src/mlx.c src/utils.c src/vec3.c \
		src/parsing/parsing_main.c src/parsing/parse_camera.c \
		src/parsing/parsing_utils.c src/parsing/parse_objects.c src/parsing/parse_info.c
		
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
	@mkdir -p $(dir $@)
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