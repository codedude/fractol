# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/01/18 13:35:13 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libtpool.a
CC			=	clang

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	../libft

SRCS		=	$(SRCD)/tp_queue.c $(SRCD)/tp_thread.c \
				$(SRCD)/tp_pool.c $(SRCD)/tp_pool2.c
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-I$(LIBFTD)/includes -I$(INCD) -O3 -flto -march=native
LDFLAGS		+=	-Wall -Wextra -Werror -std=c11 -pedantic -Wno-unused-result
LDLIBS		+=

.PHONY: clean fclean re showlib

all: $(NAME)

$(NAME): $(OBJS)
	@ar rs $@ $(OBJS)
	@echo "libtpool - compiled"

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $< $(LDLIBS)

showlib: $(NAME)
	@ar -t $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "libtpool - objects cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "libtpool - lib cleaned"

__fclean:
	@rm -f $(NAME)
	@echo "libtpool - lib cleaned"

re: fclean all