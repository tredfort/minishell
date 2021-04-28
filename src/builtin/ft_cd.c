/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 22:20:38 by smephest          #+#    #+#             */
/*   Updated: 2021/04/28 22:20:38 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	g_mini.status = 0;
	old_pwd = getcwd(NULL, 0);
	if ((!argv || !*argv) && chdir(get_value(*envp, "HOME")) == -1)
	{
		ft_strerror("HOME not set", "cd");
		g_mini.status = 1;
	}
	else if (argv && argv[0] && chdir(argv[0]) == -1)
	{
		ft_strerror(strerror(errno), "cd");
		g_mini.status = 1;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		replace_value("PWD", pwd, envp);
		free(pwd);
		replace_value("OLDPWD", old_pwd, envp);
	}
	free(old_pwd);
}
