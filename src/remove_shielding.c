/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_shielding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 01:14:55 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/22 01:15:00 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	skip_shielding_and_copy(char **str, char *tmp, int *i, int *j)
{
	if (tmp[*i] == '\\' && ++(*i))
		(*str)[(*j)++] = tmp[(*i)++];
	else if (tmp[*i] == '"' && ++(*i))
	{
		while (tmp[*i] && tmp[*i] != '"')
		{
			if (tmp[*i] == '\\' && ft_strchr("\\\"$", tmp[*i + 1]))
				(*i)++;
			(*str)[(*j)++] = tmp[(*i)++];
		}
		(*i)++;
	}
	else if (tmp[(*i)] == '\'' && ++(*i))
	{
		while (tmp[(*i)] && tmp[(*i)] != '\'')
			(*str)[(*j)++] = tmp[(*i)++];
		(*i)++;
	}
	else
		(*str)[(*j)++] = tmp[(*i)++];
}

void	remove_shielding(char **str)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = *str;
	*str = ft_calloc(ft_strlen(tmp) + 1, sizeof(char));
	if (!*str)
		exit(errno);
	i = 0;
	j = 0;
	while (tmp[i])
		skip_shielding_and_copy(str, tmp, &i, &j);
	free(tmp);
}
