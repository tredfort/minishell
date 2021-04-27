#include "../../includes/minishell.h"

void
	ft_free_str_arr(char **str)
{
	char **s;

	s = str;
	while(*s)
	{
		free(*s);
		++s;
	}
	free(str);
}
