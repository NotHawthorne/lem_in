# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alkozma <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/13 18:06:36 by alkozma           #+#    #+#              #
#    Updated: 2019/05/11 16:11:47 by alkozma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRCS = main.c \
	   data.c \
	   path.c \
	   flow.c \
	   printer.c \
	   ft_hash.c

OBJECTS = $(patsubst %.c,%.o,$(SRCS))

HEADERS = lem_in.h \
		  includes/ftgnl.h \
		  includes/ft_printf.h \
		  includes/libft.h \
		  ft_hashtables.h

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address

all: $(NAME)

$(NAME):
	make -C libft
	cp libft/libft.a ./
	gcc $(SRCS) libft.a -I includes $(FLAGS) -o $(NAME)

clean:
	make -C libft clean
	rm -rf $(OBJECTS)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME) libft.a

re: fclean all
