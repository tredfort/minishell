/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_item_from_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:32:56 by smephest          #+#    #+#             */
/*   Updated: 2021/04/26 23:33:10 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void
	remove_item_from_array(char ***root, char *del_item)
{
	char	**t;
	size_t	i;
	char	*key;

	t = *root;
	i = 0;
	while (t[i])
	{
		key = get_key_env_item(t[i]);
		if (!strcmp(key, del_item))
		{
			free(t[i]);
			while (t[i])
			{
				t[i] = t[i + 1];
				++i;
			}
			free(key);
			break ;
		}
		free(key);
		++i;
	}
}
