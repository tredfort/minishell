#include "../../includes/minishell.h"

void
	add_var(char *str, char ***env)
{
	char **t;
	char **new_t;
	char **new;
	size_t i;

	i = key_exists(get_key_env_item(str), *env);
	if (i != -1)
		(*env)[i] = ft_strdup(str);
	else
	{
		t = *env;
		new = ft_calloc(ft_strarr_size(t) + 2, sizeof(char*));
		new_t = new;
		while(t && *t)
		{
			*new_t = *t;
			++new_t;
			++t;
		}
		*new_t = ft_strdup(str);
		*env = new;
	}
}