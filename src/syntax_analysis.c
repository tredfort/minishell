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

char	skip_quotes(char *s, int *i)
{
	char	quote;

	quote = s[*i];
	while (s[++(*i)] && quote)
	{
		if (s[*i] == '\\' && s[*i + 1] == '"')
			*i += 2;
		if ((s[*i] == '"' || s[*i] == '\'') && s[*i] == quote)
			quote = 0;
	}
	return (quote);
}

char	*syntax_analysis(char *line)
{
	char	quote;
	char	prev;
	int		i;

	prev = 0;
	quote = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '\\' && !line[i + 1])
			return (ERROR_MSG13);
		if (line[i] == '\\' && ft_strchr("'\"|\\<>$; ", line[i + 1]))
			i += 2;
		if (line[i] == '"' || line[i] == '\'')
			quote = skip_quotes(line, &i);
		if (!ft_strncmp(line + i, ";;", 2))
			return (ERROR_MSG6);
		if (line[i] == ';' && ft_strchr("<>|", prev))
			return (ERROR_MSG5);
		if (line[i] == '(')
			return (ERROR_MSG3);
		if (line[i] == ')')
			return (ERROR_MSG4);
		if (!ft_strncmp(line + i, "||", 2) && (ft_strchr("<>;", prev) ||
			!after_space(line + i + 2)))
			return (ERROR_MSG2);
		if (line[i] == '|' && (ft_strchr("<>;", prev) ||
			!after_space(line + i + 1)))
			return (ERROR_MSG1);
		if ((line[i] == '>' && after_space(line + i + 1) == '<') ||
			(line[i] == '<' && after_space(line + i + 2) == '<'))
			return (ERROR_MSG10);
		if ((line[i] == '<' && after_space(line + i + 1) == '>') ||
			(line[i] == '>' && after_space(line + i + 2) == '>'))
			return (ERROR_MSG11);
		if (!ft_strncmp(line + i, "<<", 2))
			return (ERROR_MSG12);
		if ((line[i] == '<' || line[i] == '>') && !after_space(line + i + 1))
			return (ERROR_MSG9);
		prev = line[i];
		if (line[i] && !ft_strchr("'\"", line[i]))
			i++;
	}
	if (quote == '\'')
		return (ERROR_MSG7);
	if (quote == '"')
		return (ERROR_MSG8);
	return 0;
}

t_list	*split_into_commades(char *line)
{
	t_list	*lst;
	t_sh	*cmd;
	int		i;
	int		start;

	lst = NULL;
	i = 0;
	start = 0;
	while (line[i])
	{
		if (line[i] == '\\' && ft_strchr("'\"|\\<>$; ", line[i + 1]))
			i += 2;
		if (line[i] == '"' || line[i] == '\'')
			skip_quotes(line, &i);
		if (!line[i + 1] || line[i] == ';')
		{
			if (!line[i + 1])
				i++;
			cmd = malloc(sizeof(t_sh));
			if (!cmd)
				exit(1);
			cmd->cmd = ft_substr(line, start, i - start);
			cmd->pipe = 0;
			ft_lstadd_back(&lst, ft_lstnew(cmd));
			start = i + 1;
		}
		if (line[i] == '|')
		{
			cmd = malloc(sizeof(t_sh));
			if (!cmd)
				exit(1);
			cmd->cmd = ft_substr(line, start, i - start);
			cmd->pipe = 1;
			ft_lstadd_back(&lst, ft_lstnew(cmd));
			start = i + 1;
		}
		if (line[i] && !ft_strchr("'\"", line[i]))
			i++;
	}
	return (lst);
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

void	search_redirects(char *s, t_list **lst)
{
	t_redir	*rd;
	int		i;
	int		start;

	i = 0;
	rd = NULL;
	*lst = NULL;
	while (s[i])
	{
		if (s[i] == '\\' && ft_strchr("'\"|\\<>$; ", s[i + 1]))
			i += 2;
		if (s[i] == '"' || s[i] == '\'')
			skip_quotes(s, &i);
		if (!ft_strncmp(s + i, ">>", 2))
		{
			i += 2;
			start = i;
			while (s[i] == ' ')
				i++;
			while (s[i] && !ft_strchr(" <>", s[i]))
				i++;
			rd = malloc(sizeof(t_redir));
			if (!rd)
				exit(1);
			rd->action = ADD;
			rd->file = ft_substr(s, start, i - start);
			ft_memset(s + start - 2, ' ', i - start + 2);
			ft_lstadd_back(lst, ft_lstnew(rd));
		}
		else if (s[i] == '>')
		{
			i++;
			start = i;
			while (s[i] == ' ')
				i++;
			while (s[i] && !ft_strchr(" <>", s[i]))
				i++;
			rd = malloc(sizeof(t_redir));
			if (!rd)
				exit(1);
			rd->action = PUT;
			rd->file = ft_substr(s, start, i - start);
			ft_memset(s + start - 1, ' ', i - start + 1);
			ft_lstadd_back(lst, ft_lstnew(rd));
		}
		else if (s[i] == '<')
		{
			i++;
			start = i;
			while (s[i] == ' ')
				i++;
			while (s[i] && !ft_strchr(" <>", s[i]))
				i++;
			rd = malloc(sizeof(t_redir));
			if (!rd)
				exit(1);
			rd->action = TAKE;
			rd->file = ft_substr(s, start, i - start);
			ft_memset(s + start - 1, ' ', i - start + 1);
			ft_lstadd_back(lst, ft_lstnew(rd));
		}
		i++;
	}
}

void	print(t_list *lst)
{
	t_sh	*cmd;
	t_list	*tmp;
	t_list	*lst_rd;
	t_redir	*rd;

	tmp = lst;
	while (lst)
	{
		cmd = lst->content;
		search_redirects(cmd->cmd, &cmd->redir);
		printf("cmd: %s\n", cmd->cmd);
		if (cmd->pipe)
			printf("pipe: yes\n");
		else
			printf("pipe: no\n");
		lst_rd = cmd->redir;
		while (lst_rd)
		{
			rd = lst_rd->content;
			if (rd->action == PUT)
				printf("> ");
			else if (rd->action == ADD)
				printf(">> ");
			else if (rd->action == TAKE)
				printf("< ");
			printf("%s\n", rd->file);
			lst_rd = lst_rd->next;
		}
		free(cmd->cmd);
		lst = lst->next;
	}
	ft_lstclear(&tmp, free);
}







































