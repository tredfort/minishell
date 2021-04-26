#include "../../includes/minishell.h"

/*
** pwd function
** https://man7.org/linux/man-pages/man3/getcwd.3.html
*/
void	ft_pwd(void)
{
	char	*res;

	res = getcwd(NULL, 0);
	ft_putendl_fd(res, STDOUT_FILENO);
	free(res);
}
