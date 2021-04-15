#include "../includes/minishell.h"

void	print(t_list *lst)
{
	t_list	*tmp;
	t_sh	*cmd;
	int		i;

	while (lst)
	{
		cmd = lst->content;
		if (cmd->argv && cmd->argv[0])
		{
			printf("cmd: %s, len = %lu\n", cmd->argv[0],
		  	ft_strlen(cmd->argv[0]));
			free(cmd->argv[0]);
			i = 1;
			while (cmd->argv[i])
			{
				printf("argv%d: %s, len = %lu\n", i, cmd->argv[i], ft_strlen(cmd->argv[i]));
				free(cmd->argv[i]);
				i++;
			}
		}
		free(cmd->argv);
		if (cmd->pipe)
			printf("pipe: yes\n");
		else
			printf("pipe: no\n");
		tmp = cmd->redir;
		while (tmp)
		{
			printf("%s\n", (char *)tmp->content);
			tmp = tmp->next;
		}
		ft_lstclear(&cmd->redir, free);
		lst = lst->next;
	}
}
