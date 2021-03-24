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

NAME =		minishell

LIBFT =		libft/libft.a

DIR_SRCS = src

DIR_OBJS = objects

SRCS =		main.c \
			get_next_line.c \
			history.c

#SRCS :=		$(addprefix $(DIR_SRCS), $(SRCS))

OBJS =		$(addprefix $(DIR_OBJS)/, $(SRCS:.c=.o))


CC = gcc

FLAGS = #-Wall -Wextra -Werror

all: $(LIBFT) $(NAME)

$(DIR_OBJS)/%.o:$(DIR_SRCS)/%.c includes/minishell.h
	mkdir -p objects
	$(CC) -g $(FLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

$(NAME): $(OBJS)
	$(CC) $^ -Llibft -lft -ltermcap -o $@

clean:
	rm -rf $(DIR_OBJS)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
