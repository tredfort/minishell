/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 20:15:30 by smephest          #+#    #+#             */
/*   Updated: 2021/04/28 22:39:35 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	execute_child_proc(int is_child_process,
					   char *bin_path, char **argv, char **envp)
{
	int	status;

	if (is_child_process)
		execve(bin_path, argv, envp);
	else
	{
		wait(&status);
		if (!g_mini.status_set)
			g_mini.status = WEXITSTATUS(status);
	}
}

int
	ft_exec_by_path(char *path,
			char **argv, char **envp, int is_child_process)
{
	char		*bin_path;
	struct stat	st;
	int			pid;

	pid = -1;
	bin_path = get_bin_path(path, argv[0]);
	if (stat(bin_path, &st) != -1 )
	{
		if (!(st.st_mode & S_IXUSR))
			return (free_and_return(&bin_path, EACCES));
		if (st.st_mode & S_IFDIR)
			return (free_and_return(&bin_path, EISDIR));
		if (!is_child_process)
		{
			pid = fork();
			if (pid < 0)
				ft_strerror(strerror(errno), argv[0]);
		}
		if (is_child_process || pid == 0)
			execve(bin_path, argv, envp);
		execute_child_proc(pid == 0 || is_child_process, bin_path, argv, envp);
		return (free_and_return(&bin_path, 0));
	}
	return (free_and_return(&bin_path, ENOENT));
}

void
	ft_exec_show_error(char *cmd, char *path, int is_child_process)
{
	if (errno == EACCES)
	{
		ft_strerror(strerror(errno), cmd);
		if (is_child_process)
			exit(126);
		if (!g_mini.status_set)
			g_mini.status = 126;
	}
	else if (errno > 0)
	{
		if (!path || !strncmp(cmd, "./", 2) || !strncmp(cmd, "../", 3)
			|| *cmd == '/')
			ft_strerror(strerror(errno), cmd);
		else
			ft_strerror("command not found", cmd);
		if (is_child_process)
			exit(127);
		if (!g_mini.status_set)
			g_mini.status = 127;
	}
}

void
	ft_exec_from_path(char **argv, char **envp, int is_child_process)
{
	char	*path;
	char	**paths;
	char	**t;
	char	*cmd;

	cmd = argv[0];
	path = get_path(envp);
	errno = 0;
	if (!path || !strncmp(cmd, "./", 2) || !strncmp(cmd, "../", 3)
		|| *cmd == '/')
		errno = ft_exec_by_path(0, argv, envp, is_child_process);
	else
	{
		paths = ft_split(path, ':');
		t = paths;
		errno = 1;
		while (t && *t && errno && errno != EISDIR && errno != EACCES)
		{
			errno = ft_exec_by_path(*t, argv, envp, is_child_process);
			++t;
		}
		ft_free_str_arr(paths);
	}
	ft_exec_show_error(cmd, path, is_child_process);
	free(path);
}

void
	ft_exec(char *cmd, char **argv, char ***envp, int is_child_process)
{
	if (cmd)
	{
		if (!ft_strcmp(cmd, "cd"))
			ft_cd(argv + 1, envp);
		else if (!ft_strcmp(cmd, "echo"))
			ft_echo(argv + 1);
		else if (!ft_strcmp(cmd, "env"))
			ft_env(*envp);
		else if (!ft_strcmp(cmd, "exit"))
			ft_exit(argv + 1);
		else if (!ft_strcmp(cmd, "export"))
			ft_export(argv + 1, envp);
		else if (!ft_strcmp(cmd, "pwd"))
			ft_pwd();
		else if (!ft_strcmp(cmd, "unset"))
			ft_unset(argv + 1, envp);
		else
			ft_exec_from_path(argv, *envp, is_child_process);
	}
	if (is_child_process)
		exit(0);
}
