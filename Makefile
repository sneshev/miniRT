# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/03 17:28:55 by mmisumi           #+#    #+#              #
#    Updated: 2026/01/18 23:05:44 by winnitytrin      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

PARSING := src/parsing

SRCS := src/main.c src/mlx.c src/utils.c src/vec3.c src/temp.c src/dynamic_array.c \
		$(PARSING)/parsing_main.c $(PARSING)/elements.c $(PARSING)/objects.c \
		$(PARSING)/valid_info1.c $(PARSING)/valid_info2.c $(PARSING)/utils.c \
		$(PARSING)/camera_utils.c
		
		
OBJS := $(patsubst src/%.c, .obj/%.o, $(SRCS))

MLX_FLAGS	:= -Lmlx_linux -lmlx -lXext -lX11 -lz
MLX_DIR		:= mlx_linux
MLX_INC		:= -Imlx_linux

LIBFT := libft/libft.a

CC := cc -Wall -Werror -Wextra -g -Iincludes $(MLX_INC) -O0

RM := rm -rf

all: $(LIBFT) minilibx .obj $(NAME)

.obj:
	mkdir -p .obj

$(LIBFT):
	make -C libft

minilibx:
	@[ -f "$(MLX_DIR)/libmlx.a" ] || (cd $(MLX_DIR) && make)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(MLX_FLAGS) -Llibft -lm -lft -o $(NAME)

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

.PHONY: all clean fclean re minilibx