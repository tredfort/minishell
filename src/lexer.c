/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:00:58 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/08 23:29:40 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	after_space(char *line)
{
	while (*line && *line == ' ')
		line++;
	return (*line);
}

char	skip_quotes(char *line, int *i)
{
	char	quote;

	quote = line[(*i)++];
	while (line[(*i)] && quote)
	{
		if ((line[*i] == '"' || line[*i] == '\'') && line[*i] == quote)
			quote = 0;
		if (line[*i] == '\\' && ft_strchr("\"|\\<>$; ", line[*i + 1]))
			*i += 2;
		else
			(*i)++;
	}
	return (quote);
}

static void	is_sintax_error(char *line, char **error, int *i)
{
	char	quote;

	quote = 0;
	if (line[*i] == '\\' && !line[*i + 1])
		*error = ERROR_MSG13;
	else if (line[*i] == '"' || line[*i] == '\'')
		quote = skip_quotes(line, i);
	if (!*error && quote == '\'' && !after_space(line + *i + 1))
		*error = ERROR_MSG7;
	else if (!*error && quote == '"' && !after_space(line + *i + 1))
		*error = ERROR_MSG8;
	else if (!ft_strncmp(line + *i, ";;", 2))
		*error = ERROR_MSG6;
	else if (line[*i] == '(')
		*error = ERROR_MSG3;
	else if (line[*i] == ')')
		*error = ERROR_MSG4;
	else if ((line[*i] == '>' && after_space(line + *i + 1) == '<')
		|| (line[*i] == '<' && after_space(line + *i + 2) == '<'))
		*error = ERROR_MSG10;
	else if ((line[*i] == '<' && after_space(line + *i + 1) == '>')
		|| (line[*i] == '>' && after_space(line + *i + 2) == '>'))
		*error = ERROR_MSG11;
}

static void	is_sintax_error2(char *line, char prev, char **error)
{
	if (!*error && *line == ';' && ft_strchr("<>|", prev))
		*error = ERROR_MSG5;
	else if (!ft_strncmp(line, "||", 2) && (ft_strchr("<>;", prev)
			|| !after_space(line + 2)))
		*error = ERROR_MSG2;
	else if (*line == '|' && (ft_strchr("<>|;", prev)
			|| !after_space(line + 1)))
		*error = ERROR_MSG1;
	else if (!ft_strncmp(line, "<<", 2))
		*error = ERROR_MSG12;
	else if ((*line == '<' || *line == '>')
		&& !after_space(line + 1))
		*error = ERROR_MSG9;
}

int	lexer(char *line)
{
	char	*error;
	char	prev;
	int		i;

	i = 0;
	prev = 0;
	error = 0;
	while (line[i] && !error)
	{
		while (line[i] == ' ')
			i++;
		is_sintax_error(line, &error, &i);
		is_sintax_error2(line + i, prev, &error);
		prev = line[i];
		if (line[i] == '\\' && ft_strchr("'\"|\\<>$; ", line[i + 1]))
			i += 2;
		else if (line[i] && !ft_strchr("'\"", line[i]))
			i++;
	}
	if (!error)
		return (0);
	ft_putstr_fd(error, STDOUT_FILENO);
	return (1);
}
