/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:27:05 by smephest          #+#    #+#             */
/*   Updated: 2021/04/26 23:27:45 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void
	add_var(char *str, char ***env)
{
	char	**t;
	char	**new_t;
	char	**new;
	size_t	i;
	char *key;

	key = get_key_env_item(str);
	i = key_exists(key, *env);
	free(key);
	if (i != -1)
	{
		free((*env)[i]);
		(*env)[i] = ft_strdup(str);
	}
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
