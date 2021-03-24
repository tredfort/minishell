#include "../../includes/minishell.h"


//TODO: do we need it?
void	*parse_dict_item(char *str)
{
	t_item	*dict_item;
	size_t 	equal_sign_pos;

	equal_sign_pos = 0;
	dict_item = malloc(sizeof(t_item));
	if (!dict_item)
	{
		//TODO: critical error, what are we going to do?
		printf("\n\n/////WARNING//// MALLOC ERROR dict_item in function parse_dict_item\n\n");
	}
	while (str[equal_sign_pos] && str[equal_sign_pos] != '=')
		++equal_sign_pos;
	dict_item->key = malloc(sizeof(char) * (equal_sign_pos));
	if (!dict_item->key)
	{
		//TODO: critical error, what are we going to do?
		printf("\n\n/////WARNING//// MALLOC ERROR dict_item->key in function parse_dict_item\n\n");
	}
	ft_memcpy(dict_item->key, str, equal_sign_pos);
	dict_item->key[equal_sign_pos] = '\0';
	if(str + equal_sign_pos + 1)
		dict_item->value = ft_strdup(str + equal_sign_pos + 1);
	else
		dict_item->value = 0;
	return (dict_item);
}

t_list	*parse_env(char **env)
{
	t_list *env_dict;

	env_dict = 0;
	while (*env)
	{
		ft_lstadd_back(&env_dict, ft_lstnew(*env));
		++env;
	}
	return (env_dict);
}