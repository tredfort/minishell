/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_formatting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 23:23:08 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/13 00:46:59 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	remove_shielding(char **str)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = *str;
	*str = malloc(ft_strlen(tmp));
	if (!*str)
		return ;
	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i] == '"' || tmp[i] == '\\')
			i++;
		else if (tmp[i] == '\'' && ++i)
		{
			while (tmp[i] && tmp[i] != '\'')
				(*str)[j++] = tmp[i++];
		}
		else
			(*str)[j++] = tmp[i++];
	}
	(*str)[j] = '\0';
	free(tmp);
}

static int	get_keys(char *str, char **key)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	*key = ft_substr(str, 0, i);
	if (*key)
		return (1);
	return (0);
}

static void	join_value(char **remainder, char **str, char **env, int *i)
{
	char	*key;

	if (!(*remainder)[*i + 1] && ++(*i))
		*str = ft_strjoin_and_free(str, *remainder);
	else
	{
		if (i > 0)
		{
			(*remainder)[*i] = '\0';
			*str = ft_strjoin_and_free(str, *remainder);
			*remainder += *i;
			*i = 0;
		}
		if (get_keys(*remainder + 1, &key))
		{
			*str = ft_strjoin_and_free(str, get_value(env, key));
			*remainder += ft_strlen(key) + 1;
			free(key);
		}
	}
}

static void	swap_key_to_value(char **str, char **env)
{
	char	*remainder;
	char	*tmp;
	int		i;

	remainder = *str;
	tmp = *str;
	*str = ft_strdup("");
	i = 0;
	while (remainder[i])
	{
		skip_shielding(remainder, &i);
		if (remainder[i] == '\'')
			skip_quotes(remainder, &i);
		if ((remainder[i] == '$' && remainder[i + 1] && remainder[i + 1] != '$')
			|| !remainder[i + 1])
			join_value(&remainder, str, env, &i);
		else
			i++;
	}
	free(tmp);
}

void	string_formatting(t_list *lst, char **env)
{
	t_sh	*cmd;
	t_list	*rd;
	int		i;

	while (lst)
	{
		cmd = lst->content;
		i = 0;
		while (cmd->argv[i])
		{
			swap_key_to_value(&cmd->argv[i], env);
			remove_shielding(&cmd->argv[i++]);
		}
		rd = cmd->redir;
		while (rd)
		{
			swap_key_to_value((char **)&rd->content, env);
			remove_shielding((char **)&rd->content);
			rd = rd->next;
		}
		lst = lst->next;
	}
}
