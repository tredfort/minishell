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

static int	get_key(char *str, char **key, int *start)
{
	int		i;

	i = 0;
	*key = NULL;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '$')
			i += 2;
		if (str[i] == '\'')
			skip_quotes(str, &i);
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '\'' || str[i + 1] == '"'))
		{
			*start = ++i;
			while (str[i] && ft_isalnum(str[i]))
				i++;
			*key = ft_substr(str, *start, i - *start);
			break ;
		}
		i++;
	}
	if (*key)
		return (1);
	return (0);
}

static void	set_value(char **str, char *value, int key_len, int start)
{
	char	*tmp;

	tmp = *str;
	*str = ft_calloc(ft_strlen(tmp) + ft_strlen(value)
			- key_len * 2 - 1, 1);
	if (!*str)
		return ;
	ft_memcpy(*str, tmp, start - 1);
	ft_strcpy(*str + start - 1, value + key_len + 1);
	ft_strcpy(*str + ft_strlen(*str), tmp + start + key_len);
	free(tmp);
}

static void	swap_key_to_value(char **str, char **env)
{
	char	*key;
	int		i;
	int		start;
	int		key_len;

	while (get_key(*str, &key, &start))
	{
		i = 0;
		key_len = ft_strlen(key);
		while (env[i])
		{
			if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
			{
				set_value(str, env[i], key_len, start);
				break ;
			}
			i++;
		}
		if (!env[i])
			ft_memset((*str) + start - 1, ' ', key_len + 1);
		free(key);
	}
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
