#include "../../includes/minishell.h"

void
	ft_env(char **envp)
{
	int	i;

	g_mini.status = 0;
	i = -1;
	while (envp[++i])
	{
		if (ft_strchr(envp[i], '='))
			ft_putendl_fd(envp[i], STDOUT_FILENO);
	}
}
