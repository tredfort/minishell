#include "../../includes/minishell.h"

void
	unset_var(char *var, char ***env)
{
	char	**t;
	size_t 	key_len;
	char	*key;

	t = *env;
	while (t && *t)
	{
		key = get_key_env_item(*t);
		key_len = ft_strlen(key);
		if (!ft_strncmp(var, key, key_len) && !var[key_len])
		{
			free(key);
			remove_item_from_array(env, var);
			break ;
		}
		free(key);
		++t;
	}
}

/**
 * show error in this format:
 * bash: unset: `=': not a valid identifier
 * @param argv
 * @param envp
 */
void
	ft_unset(char **argv, char ***envp)
{
	char	*error_left;
	char	*error;

	while(argv && *argv)
	{
		if (validate_var(*argv))
			unset_var(*argv, envp);
		else
		{
			error_left = ft_strjoin("`", *argv);
			error = ft_strjoin(error_left, "': not a valid identifier");
			ft_strerror(error, "unset");
			free(error_left);
			free(error);
			g_mini.status = 1;
		}
		++argv;
	}
}