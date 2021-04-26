/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:18:42 by smephest          #+#    #+#             */
/*   Updated: 2021/04/26 23:24:00 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	stop_processes(t_list *proc_list)
{
	t_proc	*proc;
	int		status;
	t_list	*t;

	t = proc_list;
	while (t)
	{
		proc = t->content;
		close(proc->fd[0]);
		close(proc->fd[1]);
		t = t->next;
	}
	while (proc_list)
	{
		proc = proc_list->content;
		waitpid(proc->pid, &status, 0);
		if (!g_mini.status_set && WIFEXITED(status))
			g_mini.status = WEXITSTATUS(status);
		proc_list = proc_list->next;
	}
	free(proc_list);
}

void
	ft_pipe(t_sh *temp, char ***envp, t_list **process)
{
	int		first_pipe;
	t_proc	*proc;
	t_proc	*p;
	t_proc	*last_proc;
	t_list	*t;

	first_pipe = *process == 0;
	proc = ft_calloc(1, sizeof(t_proc));
	if (!proc || pipe(proc->fd) == -1)
		exit(errno);
	proc->pid = fork();
	if (proc->pid == -1)
		exit(errno);
	if (proc->pid == 0)
	{
		t = *process;
		while (t)
		{
			p = t->content;
			close(p->fd[1]);
			if (t->next != 0)
				close(p->fd[0]);
			t = t->next;
		}
		if (temp->pipe
			&& (!temp->redir || *((char *)(temp->redir)->content) == '<'))
			dup2(proc->fd[1], STDOUT_FILENO);
		if (!first_pipe)
		{
			last_proc = ft_lstlast(*process)->content;
			dup2(last_proc->fd[0], STDIN_FILENO);
		}
		close(proc->fd[0]);
		close(proc->fd[1]);
		ft_exec(temp->argv[0], temp->argv, envp, 1);
	}
	else
		ft_lstadd_back(process, ft_lstnew(proc));
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
	if (new_fd == -1 || dup2(new_fd, flags != O_RDONLY) == -1 || close(new_fd) == -1)
	{
		ft_strerror_fd(strerror(errno), file, 2);
		return (-1);
	}
	return (0);
}

void
	ft_executor(t_list *lst, char ***envp)
{
	t_sh	*cmd;
	t_list	*process;
	t_list	*redir;
	int		init_fd[2];
	int		redir_flag;
	char	*str;

	process = 0;
	while (lst)
	{
		redir_flag = 0;
		cmd = lst->content;
		redir = cmd->redir;
		if (redir)
		{
			redir_flag = 1;
			init_fd[0] = dup(0);
			init_fd[1] = dup(1);
		}
		while (redir)
		{
			str = redir->content;
			if (open_redir(str) == -1)
			{
				redir_flag = -1;
				break ;
			}
			redir = redir->next;
		}
		if (redir_flag != -1 && cmd->argv)
		{
			if (cmd->pipe || process != 0)
				ft_pipe(cmd, envp, &process);
			else
				ft_exec(cmd->argv[0], cmd->argv, envp, 0);
		}
		if (redir_flag != 0)
		{
			dup2(init_fd[0], 0);
			dup2(init_fd[1], 1);
			close(init_fd[0]);
			close(init_fd[1]);
		}
		lst = lst->next;
	}
	if (process != 0)
		stop_processes(process);
}
