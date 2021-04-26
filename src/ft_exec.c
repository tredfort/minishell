//
// Created by Shandy Mephesto on 4/6/21.
//

#include "../includes/minishell.h"

char
	*get_bin_path(char *path, char *cmd)
{
	char		*bin_path;
	char		*bin_path_slash;

	if (path)
	{
		bin_path_slash = ft_strjoin(path, "/");
		bin_path = ft_strjoin(bin_path_slash, cmd);
		free(bin_path_slash);
	}
	else
		bin_path = cmd;
	return (bin_path);
}

void
	some_function(int is_child_process,
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
	char		*cmd;

	cmd = argv[0];
	bin_path = get_bin_path(path, cmd);
	if (stat(bin_path, &st) != -1 )
	{
		if (!(st.st_mode & S_IXUSR))
			return (EACCES);
		if (st.st_mode & S_IFDIR)
			return (EISDIR);
		if (!is_child_process)
		{
			pid = fork();
			if (pid < 0)
				ft_strerror_fd(strerror(errno), cmd, 2);
		}
		some_function(pid == 0 || is_child_process, bin_path, argv, envp);
		return (0);
	}
	return (ENOENT);
}

void
	ft_exec_show_error(char *cmd, char *path, int is_child_process)
{
	if (errno == EACCES)
	{
		ft_strerror_fd(strerror(errno), cmd, 2);
		if (is_child_process)
			exit(126);
		if (!g_mini.status_set)
			g_mini.status = 126;
	}
	else if (errno > 0)
	{
		if (!path || !strncmp(cmd, "./", 2) || *cmd == '/')
			ft_strerror_fd(strerror(errno), cmd, 2);
		else
			ft_strerror_fd("command not found", cmd, 2);
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
	if (!path || !strncmp(cmd, "./", 2) || *cmd == '/')
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
		free(paths);
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
			ft_env(argv + 1, *envp);
		else if (!ft_strcmp(cmd, "exit"))
			ft_exit(argv + 1);
		else if (!ft_strcmp(cmd, "export"))
			ft_export(argv + 1, envp);
		else if (!ft_strcmp(cmd, "pwd"))
			ft_pwd(argv + 1);
		else if (!ft_strcmp(cmd, "unset"))
			ft_unset(argv + 1, envp);
		else
			ft_exec_from_path(argv, *envp, is_child_process);
	}
	if (is_child_process)
		exit(0);
}
