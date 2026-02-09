# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/03 17:28:55 by mmisumi           #+#    #+#              #
#    Updated: 2026/02/09 17:06:23 by sneshev          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

PARSING		:= src/parsing
MLX			:= src/mlx
UTILS		:= src/utils
RENDERING	:= src/rendering
VEC3		:=src/vec3

SRCS := src/main.c src/temp.c \
		$(MLX)/initialize.c $(MLX)/misc.c \
		$(UTILS)/utils.c $(UTILS)/dynamic_array.c \
		$(VEC3)/vec3.c $(VEC3)/vec3_compare.c \
		$(PARSING)/parsing_main.c $(PARSING)/elements.c $(PARSING)/objects.c \
		$(PARSING)/valid_info1.c $(PARSING)/valid_info2.c $(PARSING)/utils1.c \
		$(PARSING)/utils2.c \
		$(RENDERING)/render.c $(RENDERING)/objects/intersect_sph.c \
		$(RENDERING)/objects/intersect_pl.c $(RENDERING)/objects/intersect_cy.c \
		$(RENDERING)/objects/intersect_light.c \
		$(RENDERING)/render_utils.c

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
	make -C mlx_linux clean

re: fclean all

.PHONY: all clean fclean re minilibx