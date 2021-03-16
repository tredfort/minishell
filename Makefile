# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tredfort <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/14 19:12:54 by tredfort          #+#    #+#              #
#    Updated: 2021/03/14 19:13:15 by tredfort         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft.a

SRCS = main.c

SRCS2 = $(addprefix src/, $(SRCS))

OBJECTS = $(SRCS2:.c=.o)

CC = gcc

FLAGS = #-Wall -Wextra -Werror

all: $(NAME)

%o : %c #includes/minishell.h
	$(CC) $(FLAGS) $< -o $@

$(LIBFT):
	make -C libft

$(NAME): $(OBJECTS)
	$(CC) $(SRCS2) -o $(NAME)

clean:
	rm -f $(OBJECTS)
	#make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
