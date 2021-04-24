//
// Created by Shandy Mephesto on 4/24/21.
//

#include "../../includes/minishell.h"

int
	validate_var(char *str)
{
	if (!str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	++str;
	while (str && *str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		++str;
	}
	return (1);
}