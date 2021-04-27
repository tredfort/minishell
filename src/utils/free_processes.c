//
// Created by Shandy Mephesto on 4/27/21.
//

#include "../../includes/minishell.h"

void free_list_item(t_proc *item)
{
	free(item);
}

void
	free_processes(t_list **t)
{
	ft_lstclear(t, (void (*)(void *))free_list_item);
}