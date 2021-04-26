/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_exists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:31:19 by smephest          #+#    #+#             */
/*   Updated: 2021/04/26 23:31:30 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int
	key_exists(char	*key, char **envp)
{
	int	i;
	int	key_len;

	key_len = (int)ft_strlen(key);
	if (envp)
	{
		i = -1;
		while (envp[++i] && envp[i][0])
		{
			if (!ft_strncmp(key, envp[i], key_len)
				&& (!envp[i][key_len] || envp[i][key_len] == '='))
				return (i);
		}
	}
	return (-1);
}
