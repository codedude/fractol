# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/02/09 10:53:31 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fractol
CC			=	clang

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	libft
LIBTPOOLD	=	libtpool
MLXD		=	minilibx_macos

SRCS		=	$(SRCD)/main.c $(SRCD)/ft_mlx.c $(SRCD)/ft_pixel.c \
				$(SRCD)/env.c $(SRCD)/compute.c $(SRCD)/binds.c \
				$(SRCD)/point.c $(SRCD)/binds2.c \
				$(SRCD)/mandel.c $(SRCD)/julia.c $(SRCD)/burning_ship.c \
				$(SRCD)/export_bmp.c $(SRCD)/export_bmp2.c
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-I$(INCD) -O3 -flto -march=native -g\
				-I$(LIBFTD)/includes -I$(LIBTPOOLD)/includes -I$(MLXD)
LDFLAGS		+=	-Wextra -Wall -Wno-unused-result
LDLIBS		+=	-L$(LIBFTD) -lft -L$(LIBTPOOLD) -ltpool -L$(MLXD) -lmlx -lm \
				-framework OpenGL -framework AppKit

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTD)
	make -C $(LIBTPOOLD)
	make -C $(MLXD)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	make -C $(LIBFTD) clean
	make -C $(LIBTPOOLD) clean
	make -C $(MLXD) clean
	@rm -vf $(OBJS)

fclean: clean
	make -C $(LIBFTD) __fclean
	make -C $(LIBTPOOLD) __fclean
	@rm -vf $(MLXD)/libmlx.a
	@rm -vf $(NAME)

re: fclean all

rer:
	@rm -f $(NAME)
	@rm -f $(OBJS)
	make $(NAME)