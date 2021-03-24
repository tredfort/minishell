#include "../../includes/minishell.h"

char *get_dict_val_by_key(char *key)
{
	t_list *t;
	t_item *i;

	t = sh.env_dict;
	while (t)
	{
		i = t->content;
		if (!strcmp(i->key, key))
			return(i->value);
		t = t->next;
	}
	return (0);
}
