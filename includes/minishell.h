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
//TODO::remove it before mark as completed
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <term.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <curses.h>
# define SHELL_BUFFER 4095

typedef struct		s_term
{
	struct	termios	basic;
	struct	termios	user;
}					t_term;

typedef struct	s_sh
{
	char		**argv;
	int			pipe;
	t_list		*redir;
}				t_sh;

typedef struct 	s_proc
{
	int 		fd[2];
	int 		pid;
}				t_proc;

typedef struct	s_2list
{
	char		*content;
	void		*prev;
	void		*next;
} 				t_2list;

char	*bash_history;

int			get_next_line(int fd, char **line);
t_2list		*ft_2lstnew(void *content);
void		ft_2lstadd_front(t_2list **lst, t_2list *new);
int			lexer(char *line);
void		parser(char *line, t_list **lst);
void		string_formatting(t_list *lst, char **env);
void		print(t_list *lst);

char		after_spaces(const char *str);
char		skip_quotes(const char *str, int *i);
void		skip_shielding(const char *str, int *i);
void		skip_spaces(const char *str, int *i);
char		*get_value(char **env, char *key);
void		ft_exec(char *cmd, char **argv, char ***envp, int is_child_process);

char		*init_history(char *path, t_2list **lst);
void		save_history(char *file, t_2list **lst);
void		get_next_command(char **env, char **line, t_2list **head);
void		input_cycle(char **line, char **tmp, t_2list **head, t_2list *item);
void		sound_signal(void);
void		ft_strdup_and_free(char **old_str, char *new_str);
void		previous_command(t_2list **lst, t_2list *head, char	**tmp, char **line);
void		next_command(t_2list **lst, char	**tmp, char **line);
void		add_buffer(char **line, char *buf);
int			my_putchar(int c);
void		clear_command_list(t_list *lst);

/*
** utils
** folder utils
*/
char			*get_current_dir();
char			*create_dict_item(void *item);
char			**parse_env(char **env);
char			*get_dict_val_by_key(char *key, char **envp);
void			remove_item_from_array(char ***root, char *del_item);
void			del_dict_item(void *list);
char			*get_value_env_item(char *str);
char			*get_key_env_item(char *str);
size_t			ft_strarr_size(char **str_arr);
void			ft_strerror_fd(char *str_error, char *cmd, int fd);

/*
** builtin functions
** builtin folder
*/
void			ft_cd(char **argv, char **envp);
void			ft_echo(char **argv);
void			ft_env(char **argv, char **envp);
void 			ft_exit(char **argv);
void			ft_export(char **argv, char ***envp);
void			ft_pwd();
void 			ft_unset(char **argv, char ***envp);

#endif
