/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:17:11 by tredfort          #+#    #+#             */
/*   Updated: 2021/03/14 19:17:13 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR_MSG1 "minishell: syntax error near unexpected token `|'\n"
# define ERROR_MSG2 "minishell: syntax error near unexpected token `||'\n"
# define ERROR_MSG3 "minishell: syntax error near unexpected token `)'\n"
# define ERROR_MSG4 "minishell: syntax error near unexpected token `<'\n"
# define ERROR_MSG5 "minishell: syntax error near unexpected token `;'\n"
# define ERROR_MSG6 "minishell: syntax error near unexpected token `;;'\n"
# define ERROR_MSG7 "minishell: syntax error near unexpected token `newline'\n"
# define ERROR_MSG8 "minishell: syntax error near unexpected token `''\n"
# define ERROR_MSG9 "minishell: syntax error near unexpected token `\"'\n"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct	s_2list
{
	char		*content;
	void		*prev;
	void		*next;
} 				t_2list;

int			get_next_line(int fd, char **line);
int			init_history(char *file, t_2list **list);
t_2list		*ft_2lstnew(void *content);
void		ft_2lstadd_front(t_2list **lst, t_2list *new);
char		*syntax_analysis(char *line);

#endif
