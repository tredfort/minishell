# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tredfort <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/14 19:12:54 by tredfort          #+#    #+#              #
#    Updated: 2021/04/28 22:30:51 by smephest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

LIBFT =		libft/libft.a

DIR_SRCS = src

SRCS =		main.c \
			get_next_line.c \
			ft_exec.c \
			ft_executor.c \
			ft_pipe.c \
			command_call_history.c \
			lexer.c \
            parser.c \
            string_formatting.c \
            input_cycle.c \
            utils_for_input.c \
            remove_shielding.c \
            utils.c \
            get_next_line.c \
            get_next_command.c \
            clear_command_list.c \
			builtin/ft_cd.c \
			builtin/ft_echo.c \
			builtin/ft_env.c \
			builtin/ft_exit.c \
			builtin/ft_export.c \
			builtin/ft_pwd.c \
			builtin/ft_unset.c \
			utils/parse_env.c \
			utils/get_home_from_env.c \
			utils/remove_item_from_array.c \
			utils/env_item.c \
			utils/ft_strerror_fd.c \
			utils/key_exists.c \
			utils/add_var.c \
			utils/validate_var.c \
			utils/get_path.c \
			utils/get_bin_path.c \
			utils/ft_fd_helper.c \
			utils/ft_free_str_arr.c \
			utils/free_processes.c \
			utils/free_and_return.c \

#SRCS :=		$(addprefix $(DIR_SRCS), $(SRCS))

DIR_OBJS = objects

OBJS = $(addprefix $(DIR_OBJS)/, $(SRCS:.c=.o))

CC = gcc

FLAGS = -Wall -Wextra -Werror

INC = includes

DEBUG = -g

all: $(LIBFT) $(DIR_OBJS) $(NAME)

$(DIR_OBJS):
	mkdir -p $@/builtin
	mkdir -p $@/utils

$(DIR_OBJS)/%.o:$(DIR_SRCS)/%.c $(INC)/minishell.h
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
