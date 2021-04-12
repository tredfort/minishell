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

#SRCS :=		$(addprefix $(DIR_SRCS), $(SRCS))

DIR_OBJS = objects

SRCS =		main.c \
			get_next_line.c \
			ft_exec.c \
			command_call_history.c \
			lexer.c \
            parser.c \
            string_formatting.c \
            print.c \
			builtin/ft_cd.c \
			builtin/ft_echo.c \
			builtin/ft_env.c \
			builtin/ft_exit.c \
			builtin/ft_export.c \
			builtin/ft_pwd.c \
			builtin/ft_unset.c \
			utils/get_current_dir.c \
			utils/parse_env.c \
			utils/get_home_from_env.c \
			utils/del_list_item.c \
			utils/remove_item_from_array.c \
			utils/env_item.c \
			utils/ft_strerror_fd.c \
			utils/ft_strarr_size.c

#SRCS :=		$(addprefix $(DIR_SRCS), $(SRCS))

OBJS = $(addprefix $(DIR_OBJS)/, $(SRCS:.c=.o))

CC = gcc

#TODO: remove before completion
LINUX_LIB = #-lncurses

FLAGS = #-Wall -Wextra -Werror

INC = -I includes/

DEBUG = -g

all: $(LIBFT) $(NAME)

OBJ_DIRS:
	mkdir -p objects
	mkdir -p objects/builtin
	mkdir -p objects/utils

$(DIR_OBJS)/%.o:$(DIR_SRCS)/%.c includes/minishell.h OBJ_DIRS
	$(CC) $(DEBUG) $(FLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

$(NAME): $(OBJS)
	$(CC) $^ $(LINUXLIB) -Llibft -lft -ltermcap -o $@

clean:
	rm -rf $(DIR_OBJS)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
