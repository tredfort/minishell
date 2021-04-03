#include "../../includes/minishell.h"

/*
** cd function
** https://man7.org/linux/man-pages/man2/chdir.2.html
** chdir return 0 on success
** TODO:: when using main2.c a
*/
void
	ft_cd(char **argv, char **envp)
{
	//TODO:: here we should print the error description
	if ((!argv && chdir(get_dict_val_by_key("HOME", envp)) == -1)
		|| (argv && argv[0] && chdir(argv[0]) == -1))
		ft_putstr_fd(ft_itoa(errno), 1);
	//else
	//	ft_putchar_fd('\n', 1);
}
