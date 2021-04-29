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

static void	search_redirects(char *line, t_list **lst)
{
	int		i;
	int		start;
	char	*redir;

	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		skip_shielding(line, &i);
		skip_quotes(line, &i);
		if (line[i] && ft_strchr("<>", line[i]))
		{
			start = i++;
			if (line[i] == '>')
				i++;
			skip_spaces(line, &i);
			while (line[i] && !ft_strchr(" <>", line[i]))
				i++;
			redir = ft_substr(line, start, i - start);
			ft_memset(line + start, SPLITTER, i - start);
			ft_lstadd_back(lst, ft_lstnew(redir));
		}
		else if (line[i] && !ft_strchr("'\"\\", line[i]))
			i++;
	}
}

static t_sh	*add_new_command(char *line, int len, int pipe)
{
	t_sh	*cmd;
	char	*tmp;
	int		i;

	cmd = malloc(sizeof(t_sh));
	if (!cmd)
		exit(errno);
	cmd->redir = NULL;
	cmd->pipe = pipe;
	tmp = ft_substr(line, 0, len);
	search_redirects(tmp, &cmd->redir);
	i = 0;
	while (tmp[i])
	{
		skip_shielding(tmp, &i);
		skip_quotes(tmp, &i);
		while (tmp[i] == ' ')
			tmp[i++] = SPLITTER;
		if (tmp[i] && !ft_strchr("'\"\\", tmp[i]))
			i++;
	}
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
	while (line[i])
	{
		skip_spaces(line, &i);
		skip_shielding(line, &i);
		skip_quotes(line, &i);
		if (ft_strchr(";|", line[i]) || (line[i] != '\\'
				&& ft_strchr(";|", after_spaces(line + i + 1)) && ++i))
		{
			if (line[i] == '|' || after_spaces(line + i) == '|')
				cmd = add_new_command(line + start, i - start, 1);
			else
				cmd = add_new_command(line + start, i - start, 0);
			ft_lstadd_back(lst, ft_lstnew(cmd));
			while ((line[i] == ' ' || line[i] == '|' || line[i] == ';') && i++)
				start = i;
		}
		if (line[i] && !ft_strchr("'\"\\", line[i]))
			i++;
	}
}
