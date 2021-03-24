#include "../../includes/minishell.h"

void
	remove_item_from_list(t_list **root, t_list *del_item)
{
	t_list	*prev;

	if (*root == del_item)
	{
		*root = (*root)->next;
		ft_lstdelone(del_item, &del_dict_item);
	}
	prev = *root;
	while (prev->next && prev->next != del_item)
		prev = prev->next;
	if (prev->next == del_item)
	{
		prev->next = del_item->next;
		ft_lstdelone(del_item, &del_dict_item);
	}
}