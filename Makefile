# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alkozma <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/13 18:06:36 by alkozma           #+#    #+#              #
#    Updated: 2019/04/21 10:40:18 by alkozma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRCS = input.c \
	   main.c \
	   path.c \
	   flow.c

OBJECTS = $(patsubst %.c,%.o,$(SRCS))

HEADERS = lem_in.h \
		  includes/ftgnl.h \
		  includes/ft_printf.h \
		  includes/libft.h

FLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME):
	make -C libft
	cp libft/libft.a ./
	gcc $(SRCS) libft.a -Iincludes $(FLAGS) -o $(NAME)

clean:
	make -C libft clean
	rm -rf $(OBJECTS)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME) libft.a

re: fclean all
