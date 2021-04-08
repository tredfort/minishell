/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:01:07 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/08 06:01:08 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define SPLITTER (-1)

void	print(t_list *lst)
{
	t_list	*tmp;
	t_list	*head;
	t_sh	*cmd;
	int		i;

	head = lst;
	while (lst)
	{
		cmd = lst->content;
		printf("cmd: %s\n", cmd->argv[0]);
		i = 1;
		while (cmd->argv[i])
		{
			printf("argv%d: %s\n", i, cmd->argv[i]);
			i++;
		}
		if (cmd->pipe)
			printf("pipe: yes\n");
		else
			printf("pipe: no\n");
		tmp = cmd->redir;
		while (tmp)
		{
			printf("%s\n", (char *)tmp->content);
			free(tmp->content);
			tmp = tmp->next;
		}
		free(cmd);
		lst = lst->next;
	}
	ft_lstclear(&head, free);
}

void	search_redirects(char *line, t_list **lst)
{
	int		i;
	int		start;
	char	*new;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			line[i++] = SPLITTER;
		if (line[i] == '"' || line[i] == '\'')
			skip_quotes(line, &i);
		if (!ft_strncmp(line + i, ">>", 2))
		{
			start = i;
			while (line[i] == ' ')
				i++;
			while (line[i] && !ft_strchr(" <>", line[i]))
				i++;
			new = ft_substr(line, start, i - start);
			ft_memset(line + start, SPLITTER, i - start);
			ft_lstadd_back(lst, ft_lstnew(new));
		}
		if (line[i] == '\\' && ft_strchr("'\"|\\<>$; ", line[i + 1]))
			i += 2;
		else if (line[i] && !ft_strchr("'\"", line[i]))
			i++;
	}
}

t_sh	*add_new_command(char *line, int len, int pipe)
{
	t_sh	*cmd;
	char	*tmp;

	cmd = malloc(sizeof(t_sh));
	if (!cmd)
		exit(1);
	cmd->redir = NULL;
	if (!line[len + 1])
		len++;
	cmd->pipe = pipe;
	tmp = ft_substr(line, 0, len);
	search_redirects(tmp, &cmd->redir);
	cmd->argv = ft_split(tmp, SPLITTER);
	free(tmp);
	return (cmd);
}

void	parser(char *line, t_list *lst)
{
	t_sh	*cmd;
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			skip_quotes(line, &i);
		if (line[i] == ';' || line[i] == '|' || !line[i + 1])
		{
			if (line[i] == ';' || !line[i + 1])
				cmd = add_new_command(line + start, i - start, 0);
			else if (line[i] == '|')
				cmd = add_new_command(line + start, i - start, 1);
			ft_lstadd_back(&lst, ft_lstnew(cmd));
			start = i + 1;
		}
		if (line[i] == '\\' && ft_strchr("'\"|\\<>$; ", line[i + 1]))
			i += 2;
		else if (line[i] && !ft_strchr("'\"", line[i]))
			i++;
	}
	free(line);
}
