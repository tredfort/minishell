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
# define ERROR_MSG3 "minishell: syntax error near unexpected token `('\n"
# define ERROR_MSG4 "minishell: syntax error near unexpected token `)'\n"
# define ERROR_MSG5 "minishell: syntax error near unexpected token `;'\n"
# define ERROR_MSG6 "minishell: syntax error near unexpected token `;;'\n"
# define ERROR_MSG7 "minishell: syntax error near unexpected token `''\n"
# define ERROR_MSG8 "minishell: syntax error near unexpected token `\"'\n"
# define ERROR_MSG9 "minishell: syntax error near unexpected token `newline'\n"
# define ERROR_MSG10 "minishell: syntax error near unexpected token `<'\n"
# define ERROR_MSG11 "minishell: syntax error near unexpected token `>'\n"
# define ERROR_MSG12 "minishell: syntax error near unexpected token `<<'\n"
# define ERROR_MSG13 "minishell: syntax error near unexpected token `\\'\n"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <term.h>
# define SHELL_BUFFER 4097

typedef struct	s_sh
{
	char		**argv;
	int			pipe;
	t_list		*redir;
}				t_sh;

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
char		skip_quotes(char *line, int *i);
int			lexer(char *line);
void		parser(char *line, t_list **lst);
void		string_formatting(t_list *lst, char **env);
void		print(t_list *lst);
void		string_formatting(t_list *lst, char **env);

/*
** utils
** folder utils
*/
char			*get_current_dir();
char			*create_dict_item(void *item);
t_list			*parse_env(char **env);
char			*get_dict_val_by_key(char *key);
void			remove_item_from_list(t_list **root, t_list *del_item);
void			del_dict_item(void *list);
char			*get_value_env_item(char *str);
char			*get_key_env_item(char *str);

/*
** builtin functions
** builtin folder
*/
void			ft_cd(char **args);
void			ft_echo(char **argv);
void			ft_env();
void 			ft_exit(char **argv);
void			ft_export(char **argv);
void			ft_pwd();
void 			ft_unset(char **argv);

#endif
