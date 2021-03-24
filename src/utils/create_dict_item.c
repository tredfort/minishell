//
// Created by Shandy Mephesto on 3/29/21.
//
#include "../../includes/minishell.h"

char
	*create_dict_item(void *item)
{
	char	*new_item;

	new_item = malloc(sizeof(char*));
	if (new_item)
	{
		new_item = item;
		return (new_item);
	}
	else
	{
		printf("\n\n/////WARNING//// MALLOC ERROR create_dict_item in function create_dict_item\n\n");
		return (0);
	}
}
