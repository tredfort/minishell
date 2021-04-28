/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 22:22:58 by smephest          #+#    #+#             */
/*   Updated: 2021/04/28 22:22:59 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	ft_exec_pipe(t_sh *temp, char ***envp, t_list **process, t_proc *proc)
{
	t_proc	*p;
	t_list	*t;
	int		first_pipe;

	first_pipe = *process == 0;
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
		p = ft_lstlast(*process)->content;
		dup2(p->fd[0], STDIN_FILENO);
	}
	close(proc->fd[0]);
	close(proc->fd[1]);
	ft_exec(temp->argv[0], temp->argv, envp, 1);
}

void
	ft_pipe(t_sh *temp, char ***envp, t_list **process, int redir_flag)
{
	t_proc	*proc;

	proc = ft_calloc(1, sizeof(t_proc));
	if (!proc || pipe(proc->fd) == -1)
		exit(errno);
	if (redir_flag != -1)
	{
		proc->pid = fork();
		if (proc->pid == -1)
			exit(errno);
		if (proc->pid == 0)
			ft_exec_pipe(temp, envp, process, proc);
	}
	ft_lstadd_back(process, ft_lstnew(proc));
}
