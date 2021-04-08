/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:01:07 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/09 00:45:16 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define SPLITTER (-1)

static void	add_instruction(char *line, int start, t_list **lst)
{
	char	*new;
	int		i;

	i = start + 2;
	while (line[i] == ' ')
		i++;
	while (line[i] && !ft_strchr(" <>", line[i]))
		i++;
	new = ft_substr(line, start, i - start);
	ft_memset(line + start, ' ', i - start);
	ft_lstadd_back(lst, ft_lstnew(new));
}

static void	search_redirects(char *line, t_list **lst)
{
	int		i;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '"' || line[i] == '\'')
			skip_quotes(line, &i);
		if (line[i] && ft_strchr("<>", line[i]))
			add_instruction(line, i, lst);
		else if (line[i] == '\\' && ft_strchr("'\"|\\<>$; ", line[i + 1]))
			i += 2;
		else if (line[i] && !ft_strchr("'\"", line[i]))
			i++;
	}
}

static void	add_splitter(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			str[i++] = SPLITTER;
		if (str[i] == '"' || str[i] == '\'')
			skip_quotes(str, &i);
		if (str[i] == '\\' && ft_strchr("'\"|\\<>$; ", str[i + 1]))
			i += 2;
		else if (str[i] && !ft_strchr("'\"", str[i]))
			i++;
	}
}

static t_sh	*add_new_command(char *line, int len, int pipe)
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
	add_splitter(tmp);
	cmd->argv = ft_split(tmp, SPLITTER);
	free(tmp);
	return (cmd);
}

void	parser(char *line, t_list **lst)
{
	t_sh	*cmd;
	int		i;
	int		start;

	i = 0;
	start = 0;
	*lst = NULL;
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
			ft_lstadd_back(lst, ft_lstnew(cmd));
			start = i + 1;
		}
		if (line[i] == '\\' && ft_strchr("'\"|\\<>$; ", line[i + 1]))
			i += 2;
		else if (line[i] && !ft_strchr("'\"", line[i]))
			i++;
	}
}
