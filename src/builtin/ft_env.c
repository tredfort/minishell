#include "../../includes/minishell.h"

void
	ft_env(char **argv, char **envp)
{
	char	**t;

	g_mini.status = 0;
	//TODO: env somehow work with env
	(void)argv;
	t = envp;
	while (t && *t)
	{
		//TODO:: don't show var with empty value
		ft_putstr_fd(*t, 1);
		ft_putchar_fd('\n', 1);
		++t;
	}
}