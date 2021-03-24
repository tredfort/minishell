//
// Created by Shandy Mephesto on 3/27/21.
//

#include "../../includes/minishell.h"

char *get_current_dir()
{
	char	*res;

	res = malloc(sizeof(char) * SHELL_BUFFER);
	getcwd(res, SHELL_BUFFER - 1);
	return (res);
}