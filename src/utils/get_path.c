/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 00:02:07 by smephest          #+#    #+#             */
/*   Updated: 2021/04/27 00:02:08 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char
	*get_path(char **envp)
{
	char	**t;
	char	*key;

	t = envp;
	while (t && *t)
	{
		key = get_key_env_item(*t);
		if (!ft_strcmp(key, "PATH"))
		{
			free(key);
			return (get_value_env_item(*t));
		}
		free(key);
		++t;
	}
	return (0);
}
