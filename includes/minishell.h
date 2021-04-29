/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:17:11 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/29 19:53:55 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR_MSG1 "minishell: syntax error near unexpected token `|'"
# define ERROR_MSG2 "minishell: syntax error near unexpected token `||'"
# define ERROR_MSG3 "minishell: syntax error near unexpected token `('"
# define ERROR_MSG4 "minishell: syntax error near unexpected token `)'"
# define ERROR_MSG5 "minishell: syntax error near unexpected token `;'"
# define ERROR_MSG6 "minishell: syntax error near unexpected token `;;'"
# define ERROR_MSG7 "minishell: syntax error near unexpected token `''"
# define ERROR_MSG8 "minishell: syntax error near unexpected token `\"'"
# define ERROR_MSG9 "minishell: syntax error near unexpected token `newline'"
# define ERROR_MSG10 "minishell: syntax error near unexpected token `<'"
# define ERROR_MSG11 "minishell: syntax error near unexpected token `>'"
# define ERROR_MSG12 "minishell: syntax error near unexpected token `<<'"
# define ERROR_MSG13 "minishell: syntax error near unexpected token `\\'"
# include "../libft/libft.h"
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

typedef struct s_sh
{
	char		**argv;
	int			pipe;
	t_list		*redir;
}				t_sh;

typedef struct s_proc
{
	int		fd[2];
	int		pid;
}				t_proc;

typedef struct s_2list
{
	char		*content;
	void		*prev;
	void		*next;
}				t_2list;

typedef struct s_mini
{
	char			*history;
	t_2list			*lst;
	struct termios	basic;
	int				status;
	int				status_set;
}				t_mini;

t_mini		g_mini;

int				get_next_line(int fd, char **line);
t_2list			*ft_2lstnew(void *content);
void			ft_2lstadd_front(t_2list **lst, t_2list *new);
int				lexer(char *line);
void			parser(char *line, t_list **lst);
void			string_formatting(t_list *lst, char **env);
void			print(t_list *lst);

char			after_spaces(const char *str);
char			skip_quotes(const char *str, int *i);
void			skip_shielding(const char *str, int *i);
void			skip_spaces(const char *str, int *i);
char			*get_value(char **env, char *key);
void			ft_exec(char *cmd,
					char **argv, char ***envp, int is_child_process);
void			ft_executor(t_list *lst, char ***envp);
void			ft_pipe(t_sh *temp,
					char ***envp, t_list **process, int redir_flag);
void			init_history(char *path);
void			save_history(void);
void			get_next_command(char **env, char **line);
void			input_cycle(char **line, char **tmp, t_2list *lst);
void			sound_signal(void);
void			ft_strdup_and_free(char **old_str, char *new_str);
void			previous_command(t_2list **lst, char **tmp, char **line);
void			next_command(t_2list **lst, char **tmp, char **line);
void			add_buffer(char **line, char *buf);
int				my_putchar(int c);
void			clear_command_list(t_list *lst);
void			enable_basic_mode(void);
void			remove_shielding(char **str);
int				is_numeric_argument(char *str);

/*
** utils
** folder utils
*/
char			*create_dict_item(void *item);
char			**init_envp(char **env);
char			*get_dict_val_by_key(char *key, char **envp);
void			remove_item_from_array(char ***root, char *del_item);
void			del_dict_item(void *list);
char			*get_value_env_item(char *str);
char			*get_key_env_item(char *str);
size_t			ft_strarr_size(char **str_arr);
void			ft_strerror(char *str_error, char *cmd);
void			add_variables(char **argv, char ***envp);
char			**init_envp_with_default_variables(char **env);
int				key_exists(char	*key, char **envp);
void			add_var(char *str, char ***env);
int				validate_var(char *str);
char			**shall_copy_env(char **env);
char			*get_path(char **envp);
char			*get_bin_path(char *path, char *cmd);
int				init_fd_arr(int *init_fd);
void			replace_fd_back(int *init_fd);
void			crutch(int *redir_flag);
void			ft_free_str_arr(char **str);
void			free_processes(t_list **t);
int				free_and_return(char **str, int status);

/*
** builtin functions
** builtin folder
*/
void			ft_cd(char **argv, char ***envp);
void			ft_echo(char **argv);
void			ft_env(char **envp);
void			ft_exit(char **argv);
void			ft_export(char **argv, char ***envp);
void			ft_pwd(void);
void			ft_unset(char **argv, char ***envp);

#endif
