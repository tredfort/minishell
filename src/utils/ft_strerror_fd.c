//
// Created by Shandy Mephesto on 4/8/21.
//
#include "../../includes/minishell.h"

void
	ft_strerror(char *str_error, char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(str_error, STDERR_FILENO);
}
