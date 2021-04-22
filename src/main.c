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

int g_exit;

static void	prompt(void)
{
	ft_putstr_fd("minishell> ", STDIN_FILENO);
}

void stop_processes(t_list *proc_list)
{
	t_proc *proc;

	while (proc_list)
	{
		proc = proc_list->content;
		close(proc->fd[0]);
		close(proc->fd[1]);
		waitpid(proc->pid, 0, 0);
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
	if (!proc)
		exit(3);
	if(pipe(proc->fd) == -1)
		exit(errno);
	//printf("new pipes are %d and %d\n", proc->fd[0], proc->fd[1]);
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
		////printf("fd[0] = %d fd[1] = %d\n", fd[0], fd[1]);
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

void
	ft_executor(t_list *lst, char ***envp)
{
	t_sh	*cmd;
	t_list 	*process;
	t_list	*redir;
	int		init_fd[2] = {dup(0), dup(1)};
	process = 0;
	while(lst)
	{
		cmd = lst->content;
		redir = cmd->redir;
		while (redir)
		{
			char *str = redir->content;
			if (*str == '<')
			{
				char *file = str + 1;
				while (*file && *file == ' ')
					file += 1;
				int new_fd = open(file, O_RDONLY, S_IRUSR | S_IWUSR, 0000644);
				if (new_fd == -1)
					ft_strerror_fd(strerror(errno), "<",1);
				//TODO:: check if dup2 succes
				dup2(new_fd, 0);
				close(new_fd);
			}
			else if(!strncmp(str, ">>", 2))
			{
				char *file = str + 2;
				while (*file && *file == ' ')
					file += 1;
				int new_fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0000644);
				if (new_fd == -1)
					//TODO:: open didn't work
					ft_strerror_fd(strerror(errno), ">>",1);
				//TODO:: check if dup2 succes
				dup2(new_fd, 1);
				close(new_fd);
			}

			else if (*str == '>')
			{
				char *file = str + 1;
				while (*file && *file == ' ')
					file += 1;
				//TODO:: setup right chmod
				int new_fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
				if (new_fd == -1)
					ft_strerror_fd(strerror(errno), ">",1);
				//TODO:: check if dup2 succes
				dup2(new_fd, 1);
				close(new_fd);
			}
			redir = redir->next;
		}
//		void redir_prep(char *str)
//		{
//			char *file = str + 1;
//			while (*file && *file == ' ')
//				file += 1;
//			int new_fd = open(file, O_RDONLY, S_IRUSR | S_IWUSR, 0000644);
//			if (new_fd == -1)
//				exit(errno);
//			//TODO:: check if dup2 succes
//			if(dup2(new_fd, 1))
//				exit(errno);
//			close(new_fd);
//		}
		if (cmd->argv)
		{
			if (cmd->pipe || process != 0)
				ft_pipe(cmd, envp, &process);
			else
				ft_exec(cmd->argv[0], cmd->argv, envp, 0);
		}
//		wait(0);
//		exit(0);
		lst = lst->next;
	}
	dup2(init_fd[0], 0);
	dup2(init_fd[1], 1);
	close(init_fd[0]);
	close(init_fd[1]);
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
		g_exit = 128 + sig_num;
		errno = 128 + sig_num;
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
	envp = parse_env(env);
	init_history(get_value(env, "HOME"));
	while (envp)
	{
		prompt();
		get_next_command(env, &line);
//		get_next_line(STDIN_FILENO, &line);
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
