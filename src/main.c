/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:15:13 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/08 23:36:52 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	prompt(void)
{
	ft_putstr_fd("minishell> ", STDIN_FILENO);
}

void stop_processes(t_list *proc_list)
{
	t_proc *proc;
	int		status;
	t_list *t;

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
//		close(proc->fd[0]);
//		close(proc->fd[1]);
		waitpid(proc->pid, &status, 0);
		//printf("status is %d\n", status);
		if (!g_mini.status_set)
		{
//			//printf("status is %d\n", status);
//			//printf("WIFEXITED%d\n", WIFEXITED(status));
//			//printf("WEXITSTATUS %d\n", WEXITSTATUS(status));
//			//printf("WIFSIGNALED %d\n", WIFSIGNALED(status));
//			//printf("WTERMSIG %d\n", WTERMSIG(status));
//			//printf("WCOREDUMP %d\n", WCOREDUMP(status));
//			//printf("WIFSTOPPED %d\n", WIFSTOPPED(status));
//			//printf("WSTOPSIG %d\n", WSTOPSIG(status));
//			//printf("WIFCONTINUED %d\n", WIFCONTINUED(status));
//
//			//printf("g_mini.status_set=%d\n", g_mini.status_set);
//			//printf("before set it was=%d\n", g_mini.status);
			if (WIFEXITED(status))
				g_mini.status = WEXITSTATUS(status);
		}
		proc_list = proc_list->next;
	}
	free(proc_list);
}

void
	ft_pipe(t_sh * temp, char ***envp, t_list **process)
{
	int first_pipe;
	t_proc *proc;
	t_proc *last_proc;

	first_pipe = *process == 0;
	proc = ft_calloc(1, sizeof(t_proc));
	if(!proc || pipe(proc->fd) == -1)
		exit(errno);
	proc->pid = fork();
	if (proc->pid == -1)
		exit(errno);
	if (proc->pid == 0)
	{
		//TODO:: maybe we need to delete it?
		t_list *t = *process;
		while(t)
		{
			t_proc *p = t->content;
			close(p->fd[1]);
			if (t->next != 0)
				close(p->fd[0]);
			t = t->next;
		}
		//////printf("fd[0] = %d fd[1] = %d\n", fd[0], fd[1]);
		// not last function in pipes commands
		// dup to stdout
		if (temp->pipe && (!temp->redir || *((char*)(temp->redir)->content) == '<'))
			dup2(proc->fd[1], STDOUT_FILENO);
		//if pipe_mode == 0 it is the first pipe
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
	int flags;

	flags = -1;
	if(!strncmp(str, ">>", 2))
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
	int 	flags;

	flags = get_flag_set_file(str, &file);
	while (*file && *file == ' ')
		file += 1;
	int new_fd = open(file, flags, 0644);
	if (new_fd == -1 || dup2(new_fd, 0) == -1 || close(new_fd) == -1)
	{
		ft_strerror_fd(strerror(errno), file, 1);
		return (-1);
	}
	return (0);
}


void
	ft_executor(t_list *lst, char ***envp)
{
	t_sh	*cmd;
	t_list 	*process;
	t_list	*redir;
	int		init_fd[2];
	int 	redir_flag;

	process = 0;
	while(lst)
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
			char *str = redir->content;
			if (open_redir(str) == -1)
			{
				redir_flag = -1;
				break;
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

void	sigint_handler(int sig_num)
{
	int stat_loc;

	wait(&stat_loc);
	enable_basic_mode();
	if (stat_loc == sig_num)
	{
		if (sig_num == SIGINT)
			ft_putchar_fd('\n', 2);
		else if (sig_num == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
		g_mini.status = 128 + sig_num;
		g_mini.status_set = 1;
		//printf("set status signal %d\n", g_mini.status);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	**envp;
	t_list	*lst;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	envp = init_envp_with_default_variables(env);
//	init_history(get_value(env, "HOME"));
	while (envp)
	{
		prompt();
		get_next_command(env, &line);
//		get_next_line(STDIN_FILENO, &line);
		g_mini.status_set = 0;
		if (line && !lexer(line))
		{
			lst = NULL;
			parser(line, &lst);
			string_formatting(lst, envp);
			ft_executor(lst, &envp);
//			print(lst);
			clear_command_list(lst);
		}
		free(line);
	}
	return (0);
}
