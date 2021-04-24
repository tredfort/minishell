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

/**
 *
 * @param key
 * @param value
 * @param envp
 */
void	replace_value(char *key, char *value, char ***envp)
{
	int		i;
	char	*tmp;
	char	*key_equal;

	if (*envp)
	{
		i = key_exists(key, *envp);
		if (i != -1)
		{
			key_equal = ft_strjoin(key, "=");
			tmp = (*envp)[i];
			(*envp)[i] = ft_strjoin(key_equal, value);
			free(key_equal);
			free(tmp);
		}
	}
}

void	ft_cd(char **argv, char ***envp)
{
	char	*pwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if ((!argv || !*argv) && chdir(get_dict_val_by_key("HOME", *envp)) == -1)
		ft_strerror_fd("HOME not set", "cd", STDERR_FILENO);
	else if (argv && argv[0] && chdir(argv[0]) == -1)
		ft_strerror_fd(strerror(errno), "cd", STDERR_FILENO);
	else
	{
		pwd = getcwd(NULL, 0);
		replace_value("PWD", pwd, envp);
		free(pwd);
		replace_value("OLDPWD", old_pwd, envp);
	}
	free(old_pwd);
}