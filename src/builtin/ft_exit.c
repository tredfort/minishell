#include "../../includes/minishell.h"

/*
** exit function
** https://stackoverflow.com/questions/55584465/exit-command-in-shell/55585103
** TODO: what should I return in case of empty args?
 * TODO:: if
*/
void
	ft_exit(char **args)
{
	if (args && args[0] && args[1])
		ft_putstr_fd("exit: too many arguments",1);
	else if (args && args[0])
	{
//		save_history();
//TODO:: ALWAys write exit before quit

		exit((unsigned char)ft_atoi(args[0]));
	}
	else
	{
//		save_history();
		exit(0);
	}
}
