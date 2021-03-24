#include "../../includes/minishell.h"

/*
** pwd function
** https://man7.org/linux/man-pages/man3/getcwd.3.html
*/
void ft_pwd()
{
	char	*res;

	res = get_current_dir();
	ft_putstr_fd(res, 1);
	ft_putchar_fd('\n',1);
	free(res);
}
