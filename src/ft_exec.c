//
// Created by Shandy Mephesto on 4/6/21.
//

#include "../includes/minishell.h"

char
	*get_path()
{
	char	**t;
	char 	*key;

	t = sh.env;
	while(t && *t)
	{
		key = get_key_env_item(*t);
		if (!ft_strcmp(key, "PATH"))
			return (get_value_env_item(*t));
		free(key);
		++t;
	}
	return (0);
}

int
	ft_exec_by_path(char *path, char *cmd, char **argv)
{
	char *bin_path;
	char *bin_path_slash;
	struct stat st;

	if (path)
	{
		bin_path_slash = ft_strjoin(path, "/");
		bin_path = ft_strjoin(bin_path_slash, cmd);
		free(bin_path_slash);
	}
	else
		bin_path = cmd;

	if (stat(bin_path, &st) != -1 && st.st_mode & S_IXUSR)
	{
		if (st.st_mode & S_IFDIR)
			return (EISDIR);
		errno = 0;
		pid_t pid = fork();
		if (pid < 0)
			ft_strerror_fd(strerror(errno), cmd, 1);
		if (pid == 0)
			execve(bin_path, argv, sh.env);
		else
			wait(0);
		return (0);
	}
	return (ENOENT);
}

void
	ft_exec_from_path(char *cmd, char **argv)
{
	char	*path;
	char	**paths;
	char	**t;

	errno = 0;
	errno = ft_exec_by_path(0, cmd, argv);
	if (errno && errno != EISDIR)
	{
		path = get_path();
		paths = ft_split(path, ':');
		free(path);
		t = paths;
		while (t && *t && errno && errno != EISDIR)
		{
			errno = 0;
			errno = ft_exec_by_path(*t, cmd, argv);
			++t;
		}
		free(paths);
	}
	if (errno > 0)
		ft_strerror_fd(strerror(errno), cmd, 1);
}

void
	ft_exec(char *cmd, char **argv)
{
	if (cmd)
	{
		if (!ft_strcmp(cmd, "cd"))
			ft_cd(argv + 1);
		else if (!ft_strcmp(cmd, "echo"))
			ft_echo(argv + 1);
		else if (!ft_strcmp(cmd, "env"))
			ft_env(argv + 1);
		else if (!ft_strcmp(cmd, "exit"))
			ft_exit(argv + 1);
		else if (!ft_strcmp(cmd, "export"))
			ft_export(argv + 1);
		else if (!ft_strcmp(cmd, "pwd"))
			ft_pwd(argv + 1);
		else if (!ft_strcmp(cmd, "unset"))
			ft_unset(argv + 1);
		else
			ft_exec_from_path(cmd, argv);
	}
}
