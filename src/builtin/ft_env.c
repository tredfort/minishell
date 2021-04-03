#include "../../includes/minishell.h"

void
	ft_env()
{
	char	**t;

	t = sh.env;
	while (t && *t)
	{
		ft_putstr_fd(*t, 1);
		ft_putchar_fd('\n', 1);
		++t;
	}
}