# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tredfort <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 18:55:11 by tredfort          #+#    #+#              #
#    Updated: 2021/02/12 00:40:15 by tredfort         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcpy.c ft_nbrlen.c ft_atoi_and_bias.c ft_revstrncmp.c ft_remove_chars.c ft_digit_capacity.c ft_strcmp.c ft_strjoin_and_free.c ft_strarr_size.c

OBJECTS = $(SRCS:.c=.o)

BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_lstsize.c ft_lstlast.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

BONUS_OBJECTS  = $(BONUS_SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -c

INCLUDES = ./

all: $(NAME)

%.o: %.c libft.h
	gcc $(FLAGS) -I $(INCLUDES) $< -o $@

$(NAME): $(OBJECTS) $(BONUS_OBJECTS)
	ar rcs $@ $(OBJECTS) $(BONUS_OBJECTS)

clean:
	rm -f $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:     all clean fclean re
