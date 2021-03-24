#include "../../includes/minishell.h"

void
	unset_var(char *var)
{
	t_list	*t;

	t = sh.env_dict;
	while (t)
	{
		if(!strncmp(t->content, var, ft_strlen(var)))
		{
			remove_item_from_list(&sh.env_dict, t);
			break ;
		}
		t = t->next;
	}
}

void
	ft_unset(char **argv)
{
	if (!argv || !*argv)
		ft_putstr_fd("unset: not enough arguments\n", 1);
	else while(*argv)
	{
		unset_var(*argv);
		++argv;
	}
}