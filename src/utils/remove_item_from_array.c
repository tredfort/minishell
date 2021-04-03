#include "../../includes/minishell.h"

void
	remove_item_from_array(char ***root, char *del_item)
{
	char	**t;
	size_t	i;
	char	*key;

	t = *root;
	i = 0;
	while(t[i])
	{
		key = get_key_env_item(t[i]);
		printf("key %s del_item %s\n", key, del_item);
		if (!strcmp(key, del_item))
		{
			printf("founded by key %s\n", key);
			while(t[i])
			{
				t[i] = t[i + 1];
				++i;
			}
			break;
		}
		free(key);
		++i;
	}
}