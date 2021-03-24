#include "../../includes/minishell.h"

char
	*get_key_env_item(char *str)
{
	size_t 	equal_sign_pos;
	char 	*key;

	equal_sign_pos = 0;
	while (str[equal_sign_pos] && str[equal_sign_pos] != '=')
		++equal_sign_pos;
	key = malloc(sizeof(char) * (equal_sign_pos));
	if (!key)
	{
		//TODO: critical error, what are we going to do?
		printf("\n\n/////WARNING//// MALLOC ERROR dict_item->key in function parse_dict_item\n\n");
	}
	ft_memcpy(key, str, equal_sign_pos);
	key[equal_sign_pos] = '\0';
	return (key);
}

char
	*get_value_env_item(char *str)
{
	size_t 	equal_sign_pos;

	equal_sign_pos = 0;
	while(str[equal_sign_pos] && str[equal_sign_pos] != '=')
		++equal_sign_pos;
	if ('=' == str[equal_sign_pos])
		return (ft_strdup(str + equal_sign_pos + 1));
	else
		return (0);
}