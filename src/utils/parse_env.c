#include "../../includes/minishell.h"
#include <stdio.h>

char	**parse_env(char **env)
{
	char	**env_dict;
	size_t	dict_size;
	size_t	i;

	dict_size = 0;
	while(env && env[dict_size])
		++dict_size;
	env_dict = ft_calloc(dict_size + 1, sizeof(char*));
	i = -1;
	while(env && env[++i])
		env_dict[i] = ft_strdup(env[i]);
	return (env_dict);
}