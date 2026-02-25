# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/03 17:28:55 by mmisumi           #+#    #+#              #
#    Updated: 2026/02/25 10:28:44 by sneshev          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

PARSING		:= src/parsing
MLX			:= src/mlx
UTILS		:= src/utils
RENDERING	:= src/rendering
OBJECTS		:= src/rendering/intersections
VEC3		:=src/vec3

SRCS := src/main.c \
		$(MLX)/initialize.c \
		$(MLX)/misc.c \
		$(UTILS)/utils.c \
		$(UTILS)/dynamic_array.c \
		$(UTILS)/dynamic_array_utils.c \
		$(VEC3)/vec3.c \
		$(VEC3)/new_vec3.c \
		$(PARSING)/parsing_main.c \
		$(PARSING)/elements.c \
		$(PARSING)/objects.c \
		$(PARSING)/valid_info1.c \
		$(PARSING)/valid_info2.c \
		$(PARSING)/utils1.c \
		$(PARSING)/utils2.c \
		$(RENDERING)/render.c \
		$(RENDERING)/rays.c \
		$(RENDERING)/rand.c \
		$(RENDERING)/render_utils.c \
		$(OBJECTS)/hit_object.c \
		$(OBJECTS)/intersect_sph.c \
		$(OBJECTS)/intersect_pl.c \
		$(OBJECTS)/intersect_cy.c \
		$(OBJECTS)/intersect_cy_side.c \
		$(OBJECTS)/intersect_light.c \
		$(OBJECTS)/quadratic.c \


OBJS := $(patsubst src/%.c, .obj/%.o, $(SRCS))

MLX_FLAGS	:= -Lmlx_linux -lmlx -lXext -lX11 -lz
MLX_DIR		:= mlx_linux
MLX_INC		:= -Imlx_linux

LIBFT := libft/libft.a

CC := cc -Wall -Werror -Wextra -g -Iincludes $(MLX_INC) -O3 -mavx2 -mfma #-fsanitize=undefined,address

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