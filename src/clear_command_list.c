/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_command_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:39:16 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/19 17:48:30 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_command_list(t_list *lst)
{
	t_list	*head;
	t_sh	*cmd;
	int		i;

	head = lst;
	while (lst)
	{
		cmd = lst->content;
		i = 0;
		if (cmd->argv)
		{
			while (cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}
		ft_lstclear(&cmd->redir, free);
		lst = lst->next;
	}
	ft_lstclear(&head, free);
}
