//
// Created by Shandy Mephesto on 4/8/21.
//
#include "../../includes/minishell.h"

void
	ft_strerror_fd(char *str_error, char *cmd, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	if (cmd)
	{
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putendl_fd(str_error, fd);
}