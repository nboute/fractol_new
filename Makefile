# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niboute <niboute@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/09 18:34:41 by niboute           #+#    #+#              #
#    Updated: 2019/10/19 15:06:59 by niboute          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol

SRC= colors.c draw.c main_events.c menu_events.c loop.c main.c menu.c \
	 setup.c fractals.c mlx_alnum_keycodes.c color_menu_events.c \
	 fractal_events.c color_menu.c

SRCDIR= src/

SRCS= $(addprefix $(SRCDIR), $(SRC))

OBJ= $(SRCS:.c=.o)

HEADER= ./inc/header.h

LIBFT= libft/libft.a

FT= -L ./libft/ -lft

LIBMLX= minilibx_macos/libmlx.a

MLX= -L ./minilibx_macos -lmlx -framework OpenGL -framework AppKit

CC= gcc

CFLAGS= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX) $(HEADER)
	$(CC) -o $@ $(OBJ) $(MLX) $(FT)

$(LIBFT):
	make -C libft/

$(LIBMLX):
	make -C minilibx_macos/ 2> /dev/null

clean:
	rm -f $(OBJ)
	make clean -C libft/
	make clean -C minilibx_macos/

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(LIBMLX)

re: clean fclean all

.PHONY: all clean fclean re
