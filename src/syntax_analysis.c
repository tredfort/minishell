/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 13:58:19 by tredfort          #+#    #+#             */
/*   Updated: 2021/03/27 13:58:24 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print(t_list *lst)
{
	t_list	*tmp;
	t_sh	*cmd;
	int		i;

	while (lst)
	{
		cmd = lst->content;
		printf("cmd: %s\n", cmd->argv[0]);
		free(cmd->argv[0]);
		i = 1;
		while (cmd->argv[i])
		{
			printf("argv%d: %s\n", i, cmd->argv[i]);
			free(cmd->argv[i]);
			i++;
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

void	swap_key_to_value(char **s, char *key, char **ev)
{
	char	*tmp;
	int		i;
	int		key_len;

	i = 0;
	tmp = *s;
	while (ev[i])
	{
		key_len = ft_strlen(key);
		if (ft_strncmp(ev[i], key, key_len) && ev[i][key_len] == '=')
			
		i++;
	}
}
