#include "../../includes/minishell.h"

void 	print_list_item(void *content)
{
	ft_putstr_fd(content, 1);
	ft_putchar_fd('\n', 1);
}

void
	ft_env()
{
	ft_lstiter(sh.env_dict, &print_list_item);
}