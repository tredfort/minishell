#include "../../includes/minishell.h"

char *get_dict_val_by_key(char *key, char **envp)
{
	char	**t;
	char	*item_key;

	t = envp;
	while (t && *t)
	{
		item_key = get_key_env_item(*t);
		if (!strcmp(item_key, key))
			return(get_value_env_item(*t));
		++t;
	}
	return (0);
}
