//
// Created by Twycross Redfort on 4/23/21.
//

#include "../../includes/minishell.h"

int	key_exists(char	*key, char **envp)
{
	int	i;
	int key_len;

	key_len = ft_strlen(key);
	if (envp)
	{
		i = -1;
		while (envp[++i] && envp[i][0])
		{
			if (!ft_strncmp(key, envp[i], key_len)
				&& (!envp[i][key_len] || envp[i][key_len] == '='))
				return (i);
		}
	}
	return (-1);
}