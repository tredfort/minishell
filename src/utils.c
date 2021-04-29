/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:18:56 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/15 13:09:10 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_shielding(const char *str, int *i)
{
	if (str[*i] == '\\' && str[*i + 1])
		*i += 2;
}

void	skip_spaces(const char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

char	after_spaces(const char *str)
{
	while (*str && *str == ' ')
		str++;
	return (*str);
}

char	skip_quotes(const char *str, int *i)
{
	char	quote;

	quote = 0;
	if (str[*i] == '"' || str[*i] == '\'')
	{
		quote = str[(*i)++];
		while (str[(*i)] && quote)
		{
			if (quote == '"')
				skip_shielding(str, i);
			if ((str[*i] == '"' || str[*i] == '\'') && str[*i] == quote)
				quote = 0;
			(*i)++;
		}
	}
	if (str[*i] == '"' || str[*i] == '\'')
		quote = skip_quotes(str, i);
	return (quote);
}

char	*get_value(char **env, char *key)
{
	int		i;
	int		key_len;

	i = -1;
	key_len = (int)ft_strlen(key);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
			return (env[i] + key_len + 1);
	}
	return ("");
}
