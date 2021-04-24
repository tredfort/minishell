//
// Created by Shandy Mephesto on 4/6/21.
//

#include "../includes/minishell.h"

char
	*get_path(char **envp)
{
	char	**t;
	char 	*key;

	t = envp;
	while(t && *t)
	{
		key = get_key_env_item(*t);
		if (!ft_strcmp(key, "PATH"))
		{
			free(key);
			return (get_value_env_item(*t));
		}
		free(key);
		++t;
	}
	return (0);
}

int
	ft_exec_by_path(char *path, char *cmd, char **argv, char **envp, int is_child_process)
{
	char *bin_path;
	char *bin_path_slash;
	struct stat st;
	int pid;
	int status;

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
		//errno = 0;
		if (!is_child_process)
		{
			pid = fork();
			if (pid < 0)
				ft_strerror_fd(strerror(errno), cmd, 1);
		}
		if (is_child_process || pid == 0)
		{
			execve(bin_path, argv, envp);
		}
		else
		{
			wait(&status);
			g_mini.status = WEXITSTATUS(status);
		}
		return (0);
	}
	return (ENOENT);
}

void
	ft_exec_from_path(char *cmd, char **argv, char **envp, int is_child_process)
{
	char	*path;
	char	**paths;
	char	**t;

//	errno = 0;
	errno = ft_exec_by_path(0, cmd, argv, envp, is_child_process);
	if (errno && errno != EISDIR)
	{
		path = get_path(envp);
		paths = ft_split(path, ':');
		free(path);
		t = paths;
		while (t && *t && errno && errno != EISDIR)
		{
			errno = 0;
			errno = ft_exec_by_path(*t, cmd, argv, envp, is_child_process);
			++t;
		}
		free(paths);
	}
	if (errno > 0)
		ft_strerror_fd(strerror(errno), cmd, 1);
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
			ft_exec_from_path(cmd, argv, *envp, is_child_process);
	}
	if (is_child_process)
		exit(0);
}
