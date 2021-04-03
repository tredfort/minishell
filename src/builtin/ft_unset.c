#include "../../includes/minishell.h"

void
	unset_var(char *var, char ***env)
{
	char	**t;
	char	*key;

	t = *env;
	while (t)
	{
		if(!strncmp(*t, var, ft_strlen(var)))
		{
			remove_item_from_array(env, var);
			break ;
		}
		++t;
	}
}

void
	ft_unset(char **argv, char ***envp)
{
	if (!argv || !*argv)
		ft_putstr_fd("unset: not enough arguments\n", 1);
	else while(*argv)
	{
		unset_var(*argv, envp);
		++argv;
	}
}