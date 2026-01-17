# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/18 14:23:34 by mmisumi           #+#    #+#              #
#    Updated: 2026/01/17 18:13:57 by winnitytrin      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

SRCS := src/ft_atoi.c src/ft_bzero.c src/ft_calloc.c src/ft_isalnum.c src/ft_isalpha.c src/ft_isascii.c src/ft_isdigit.c src/ft_isprint.c \
		src/ft_itoa.c src/ft_memchr.c src/ft_memcmp.c src/ft_memcpy.c src/ft_memmove.c src/ft_memset.c src/ft_putchar_fd.c \
		src/ft_putendl_fd.c src/ft_putnbr_fd.c src/ft_putstr_fd.c src/ft_split.c src/ft_strchr.c src/ft_strdup.c \
		src/ft_striteri.c src/ft_strjoin.c src/ft_strlcat.c src/ft_strlcpy.c src/ft_strlen.c \
		src/ft_strmapi.c src/ft_strncmp.c src/ft_strnstr.c src/ft_strrchr.c \
		src/ft_strtrim.c src/ft_substr.c src/ft_tolower.c \
		src/ft_toupper.c src/get_next_line.c src/get_next_line_utils.c


OBJS := $(addprefix obj/, $(notdir $(SRCS:.c=.o)))

CC := cc
CFLAGS := -Wall -Werror -Wextra -I.

RM := rm -rf

all: obj $(NAME)

obj:
	mkdir -p obj

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

obj/%.o: src/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJS) $(RM) obj

fclean: clean
	$(RM) $(NAME)


re: fclean all

.PHONY: all clean fclean re
