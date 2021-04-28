/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:27:05 by smephest          #+#    #+#             */
/*   Updated: 2021/04/28 22:32:18 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t
	get_key_index(char *str, char ***env)
{
	char	*key;
	size_t	i;

	key = get_key_env_item(str);
	i = key_exists(key, *env);
	free(key);
	return (i);
}

void
	replace_var(size_t i, char ***env, char *str)
{
	free((*env)[i]);
	(*env)[i] = ft_strdup(str);
}

void
	add_var(char *str, char ***env)
{
	char	**t;
	char	**new_t;
	char	**new;
	int		i;

	i = get_key_index(str, env);
	if (i != -1)
		replace_var(i, env, str);
	else
	{
		t = *env;
		new = ft_calloc(ft_strarr_size(t) + 2, sizeof(char *));
		new_t = new;
		while (t && *t)
		{
			*new_t = *t;
			++new_t;
			++t;
		}
		*new_t = ft_strdup(str);
		free(*env);
		*env = new;
	}
}
