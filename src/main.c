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
	t_list *t = proc_list;
	while (t)
	{
		proc = t->content;
		//printf("ex pid = %d\n", proc->pid);
		t = t->next;
	}
	while (proc_list)
	{
		proc = proc_list->content;
		close(proc->fd[0]);
		close(proc->fd[1]);
		//printf("close fd[0, 1] = { %d, %d }\n", proc->fd[0], proc->fd[1]);
		waitpid(proc->pid, 0, 0);
		//printf("close pid = %d\n", proc->pid);
		proc_list = proc_list->next;
	}
	free(proc_list);
	//printf("ended wait\n");
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
	//TODO:: what do we need to do in case of this error?
	// opt1 : print error exit
	// opt2 : print error terminate command continue working
	if(pipe(proc->fd) == -1)
		exit(1);
	//printf("new pipes are %d and %d\n", proc->fd[0], proc->fd[1]);
	proc->pid = fork();
	//TODO:: what do we need to do in case of this error?
	// opt1 : print error exit
	// opt2 : print error terminate command continue working
	if (proc->pid == -1)
		exit(1);
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
		if (temp->pipe)
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
	else{
		t_list *new = ft_lstnew(proc);
		t_proc *p = new->content;
		//printf("added new list id = %d fd[0,1] = %d %d\n", p->pid, p->fd[0], p->fd[1]);
		ft_lstadd_back(process, ft_lstnew(proc));
	}
}

void
	ft_executor(t_list *lst, char ***envp)
{
	t_sh	*temp;
	t_list 	*process;
	t_list	*redir;
	int		init_fd[2] = {dup(0), dup(1)};
	process = 0;
	while(lst)
	{
		temp = lst->content;
		redir = temp->redir;
		while (redir)
		{
			char *str = redir->content;
			if (*str == '<')
			{
				char *file = str + 1;
				while (*file && *file == ' ')
					file += 1;
				int new_fd = open(file, O_RDONLY, S_IRUSR | S_IWUSR);
				//printf("new fd for read = %d\n", new_fd);
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
				int new_fd = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
				//printf("new fd for >> = %d\n", new_fd);
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
				//printf("will execute open\n");
				//sleep(10);
				int new_fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
				//printf("new fd for > = %d\n", new_fd);
				//sleep(10);
				if (new_fd == -1)
					ft_strerror_fd(strerror(errno), ">",1);
				//TODO:: check if dup2 succes
				dup2(new_fd, 1);
				close(new_fd);
			}
			redir = redir->next;
		}
		if (temp->argv)
		{
			if (temp->pipe || process != 0)
				ft_pipe(temp, envp, &process);
			else
				ft_exec(temp->argv[0], temp->argv, envp, 0);
		}
		lst = lst->next;
	}
	dup2(init_fd[0], 0);
	dup2(init_fd[1], 1);
	close(init_fd[0]);
	close(init_fd[1]);
	if (process != 0)
	{
		t_list *t = process;
		t_proc *p;
		while (t)
		{
			p = t->content;
			//printf("shows list id = %d fd[0,1] = %d %d\n", p->pid, p->fd[0], p->fd[1]);
			t = t->next;
		}
		stop_processes(process);
	}
}

void	sigint_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		prompt();
		//signal(SIGINT, sigint_handler);
	}
	else if (sig_num == SIGQUIT)
	{
		//force_stop child process
		ft_putstr_fd("Quit: ", 2);
		ft_putnbr_fd(sig_num, 2);
		ft_putendl_fd(NULL, 2);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	**envp;
	t_list	*lst;
	t_2list	*history;
	t_sh	*temp;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	envp = parse_env(env);
	bash_history = init_history(get_value(env, "HOME"), &history);
	while (envp)
	{
		prompt();
		get_next_command(env, &line, &history);
//		get_next_line(STDIN_FILENO, &line);
		if (line && !lexer(line))
		{
			lst = NULL;
			parser(line, &lst);
			string_formatting(lst, envp);
			ft_executor(lst, &envp);
//			print(lst);
//			executor(lst, env);
//			ft_lstclear(&lst, free);
			clear_command_list(lst);
			//printf("errno is %d\n", errno);
		}
//		free(line);
	}
	return (0);
}
