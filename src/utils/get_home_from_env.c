/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_home_from_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 22:21:56 by smephest          #+#    #+#             */
/*   Updated: 2021/04/28 22:21:56 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_dict_val_by_key(char *key, char **envp)
{
	char	**t;
	char	*item_key;

	t = envp;
	while (t && *t)
	{
		item_key = get_key_env_item(*t);
		if (!strcmp(item_key, key))
		{
			free(item_key);
			return (get_value_env_item(*t));
		}
		free(item_key);
		++t;
	}
	return (0);
}
