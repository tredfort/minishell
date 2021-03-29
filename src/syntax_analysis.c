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

char	*syntax_analysis(char *line)
{
	char	quotes;
	char	prev;

	prev = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (prev != '\\' && (*line == '"' || *line == '\''))
		{
			quotes = *line;
			while (*(++line) && quotes)
				if (*line == quotes)
					quotes = 0;
		}
		if (prev != '\\' && *line == '(')
		{
			quotes = *line;
			while (*(++line) && quotes)
				if (*line == ')')
					quotes = 0;
		}
		if ((!prev || prev == ';') && *line == '|' && *(line + 1) == '|')
			return (ERROR_MSG2);
		if ((!prev || prev == ';') && *line == '|')
			return (ERROR_MSG1);
		if (prev != '\\' && *line == ')')
			return (ERROR_MSG3);
		if (prev != '\\' && *line == '>' && *(line + 1) == '<')
			return (ERROR_MSG4);
		if ((!prev || prev != '\\') && *line == ';' && *(line + 1) == ';')
			return (ERROR_MSG6);
		if ((!prev || prev != '\\') && *line == ';')
			return (ERROR_MSG5);
//		if ((!prev || prev != '\\') && *line == ';')
//			return (ERROR_MSG5);
		prev = *line;
		line++;
	}
	if (quotes == '\'')
		return (ERROR_MSG8);
	if (quotes == '"')
		return (ERROR_MSG9);
	return 0;
}
