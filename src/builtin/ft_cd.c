#include "../../includes/minishell.h"

/*
** cd function
** https://man7.org/linux/man-pages/man2/chdir.2.html
** chdir return 0 on success
** TODO:: when using main2.c a
*/
//void
//	ft_cd(char **argv, char **envp)
//{
//	//TODO:: here we should print the error description
//	if ((!argv && chdir(get_dict_val_by_key("HOME", envp)) == -1)
//		|| (argv && argv[0] && chdir(argv[0]) == -1))
//		ft_putstr_fd(ft_itoa(errno), 1);
//	//else
//	//	ft_putchar_fd('\n', 1);
//}

void	ft_cd(char **argv, char ***envp)
{
	char	*pwd;
	char	*old_pwd;
	char	**arr;

	old_pwd = getcwd(NULL, 0);
	if (!argv && chdir(get_dict_val_by_key("HOME", *envp)) == -1)
		ft_strerror_fd("HOME not set", "cd", STDERR_FILENO);
	else if (argv && argv[0] && chdir(argv[0]) == -1)
		ft_strerror_fd(strerror(errno), "cd", STDERR_FILENO);
	else
	{
		pwd = getcwd(NULL, 0);
		if (key_exists("PWD", *envp))
			add_variables(&pwd, envp);
		free(pwd);
		if (key_exists("OLDPWD", *envp))
			add_variables(&old_pwd, envp);
	}
	free(old_pwd);
}