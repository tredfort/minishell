/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_formatting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 23:23:08 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/10 23:23:10 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define SPLITTER (-1)

void	print(t_list *lst)
{
	t_list	*tmp;
	t_sh	*cmd;
	int		i;

	while (lst)
	{
		cmd = lst->content;
		if (cmd->argv[0])
		{
			printf("cmd: %s\n", cmd->argv[0]);
			free(cmd->argv[0]);
			i = 1;
			while (cmd->argv[i])
			{
				printf("argv%d: %s\n", i, cmd->argv[i]);
				free(cmd->argv[i]);
				i++;
			}
		}
		free(cmd->argv);
		if (cmd->pipe)
			printf("pipe: yes\n");
		else
			printf("pipe: no\n");
		tmp = cmd->redir;
		while (tmp)
		{
			printf("%s\n", (char *)tmp->content);
			tmp = tmp->next;
		}
		ft_lstclear(&cmd->redir, free);
		lst = lst->next;
	}
}

void	remove_shielding(char **str)
{
	int		i;
	char	*ptr;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\"')
			(*str)[i] = SPLITTER;
		if ((*str)[i] == '\'')
		{
			ptr = *str + i;
			skip_quotes(*str, &i);
			*ptr = SPLITTER;
			(*str)[i - 1] = SPLITTER;
		}
		if ((*str)[i] == '\\' && i++)
			(*str)[i - 1] = SPLITTER;
		i++;
	}
	i = 0;
	int j = 0;
	ptr = *str;
	*str = ft_calloc(ft_strlen(ptr), sizeof(char));
	while (ptr[i])
	{
		if (ptr[i] != SPLITTER)
			(*str)[j++] = ptr[i];
		i++;
	}
	(*str)[j] = '\0';
	free(ptr);
}

int	get_key(char *str, char **key, int *start)
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
		if (str[i] == '$' && str[i + 1] != '$')
		{
			i++;
			*start = i;
			while (str[i] && ft_isalnum(str[i]))
				i++;
			*key = ft_substr(str, *start, i - *start);
			break;
		}
		i++;
	}
	if (*key)
		return (1);
	return 0;
}

void	swap_key_to_value(char **str, char **env)
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
				char *tmp = *str;
				*str = ft_calloc(ft_strlen(tmp) + ft_strlen(env[i])
						- key_len * 2 - 1, 1);
				ft_memcpy(*str, tmp, start - 1);
				ft_strcpy(*str + start - 1, env[i] + key_len + 1);
				ft_strcpy(*str + ft_strlen(*str), tmp + start + key_len);
				free(tmp);
				break;
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
