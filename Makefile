# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/01/11 15:23:13 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fractol
CC			=	gcc

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	libft
MLXD		=	minilibx_macos

SRCS		=	$(SRCD)/main.c $(SRCD)/ft_mlx.c $(SRCD)/ft_pixel.c \
				$(SRCD)/env.c $(SRCD)/compute.c $(SRCD)/binds.c
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-I$(INCD) -I$(LIBFTD)/includes -I$(MLXD) -O3 -g
#Warnigs and debug
LDFLAGS		+=	-Wextra -Wall -ansi -pedantic -Wno-unused-result
LDLIBS		+=	-L$(LIBFTD) -lft -L$(MLXD) -lmlx -lm \
				-framework OpenGL -framework AppKit

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTD)
	make -C $(MLXD)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	make -C $(LIBFTD) clean
	make -C $(MLXD) clean
	@rm -vf $(OBJS)

fclean: clean
	make -C $(LIBFTD) __fclean
	@rm -vf $(MLXD)/libmlx.a
	@rm -vf $(NAME)

re: fclean all

rer:
	@rm -f $(NAME)
	@rm -f $(OBJS)
	make $(NAME)