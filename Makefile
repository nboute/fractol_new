# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niboute <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/09 18:34:41 by niboute           #+#    #+#              #
#    Updated: 2019/03/22 06:42:48 by niboute          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf

SRC= colors.c draw_lines.c events.c events_2.c loop.c main.c menu.c parser.c \
	 setup.c

SRCDIR= src/

SRCS= $(addprefix $(SRCDIR), $(SRC))

OBJ= $(SRCS:.c=.o)

LIBFT= libft/libft.a

FT= -L ./libft/ -lft

LIBMLX= minilibx_macos/libmlx.a

MLX= -L ./minilibx_macos -lmlx -framework OpenGL -framework AppKit

CC= gcc

CFLAGS= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX)
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(MLX) $(FT)

$(LIBFT):
	make -C libft/

$(LIBMLX):
	make -C minilibx_macos/

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
