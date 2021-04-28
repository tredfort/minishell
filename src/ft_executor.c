/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:18:42 by smephest          #+#    #+#             */
/*   Updated: 2021/04/27 20:17:05 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	stop_processes(t_list **proc_list)
{
	t_proc	*proc;
	int		status;
	t_list	*t;

	t = *proc_list;
	while (t)
	{
		proc = t->content;
		close(proc->fd[0]);
		close(proc->fd[1]);
		t = t->next;
	}
	t = *proc_list;
	while (t)
	{
		proc = t->content;
		waitpid(proc->pid, &status, 0);
		if (!g_mini.status_set && WIFEXITED(status))
			g_mini.status = WEXITSTATUS(status);
		t = t->next;
	}
	free_processes(proc_list);
}

int
	get_flag_set_file(char *str, char **file)
{
	int	flags;

	flags = -1;
	if (!strncmp(str, ">>", 2))
	{
		*file = str + 2;
		flags = O_CREAT | O_WRONLY | O_APPEND;
	}
	else
	{
		*file = str + 1;
		if (*str == '<')
			flags = O_RDONLY;
		else if (*str == '>')
			flags = O_CREAT | O_WRONLY | O_TRUNC;
	}
	return (flags);
}

int
	open_redir(char *str)
{
	char	*file;
	int		flags;
	int		new_fd;

	flags = get_flag_set_file(str, &file);
	while (*file && *file == ' ')
		file += 1;
	new_fd = open(file, flags, 0644);
	if (new_fd == -1
		|| dup2(new_fd, flags != O_RDONLY) == -1
		|| close(new_fd) == -1)
	{
		ft_strerror(strerror(errno), file);
		return (-1);
	}
	return (0);
}

void
	ft_exec_cmd(t_sh *cmd, t_list **process, char ***envp)
{
	int		init_fd[2];
	int		redir_flag;
	t_list	*redir;

	redir = cmd->redir;
	redir_flag = 0;
	if (redir)
		redir_flag = init_fd_arr(init_fd);
	while (redir_flag != -1 && redir)
	{
		if (open_redir(redir->content) == -1)
			crutch(&redir_flag);
		redir = redir->next;
	}
	if (cmd->argv)
	{
		if (cmd->pipe || *process != 0)
			ft_pipe(cmd, envp, process, redir_flag);
		else if (redir_flag != -1)
			ft_exec(cmd->argv[0], cmd->argv, envp, 0);
	}
	if (redir_flag != 0)
		replace_fd_back(init_fd);
}

void
	ft_executor(t_list *lst, char ***envp)
{
	t_list	*process;

	process = 0;
	while (lst)
	{
		ft_exec_cmd(lst->content, &process, envp);
		if (process != 0 && !((t_sh *) lst->content)->pipe)
			stop_processes(&process);
		lst = lst->next;
	}
}
