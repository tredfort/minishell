/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:29:24 by smephest          #+#    #+#             */
/*   Updated: 2021/04/26 23:29:26 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char
	*get_key_env_item(char *str)
{
	size_t	equal_sign_pos;
	char	*key;

	equal_sign_pos = 0;
	while (str[equal_sign_pos] && str[equal_sign_pos] != '=')
		++equal_sign_pos;
	key = malloc(sizeof(char) * (equal_sign_pos));
	if (!key)
		exit(errno);
	ft_memcpy(key, str, equal_sign_pos);
	key[equal_sign_pos] = '\0';
	return (key);
}

char
	*get_value_env_item(char *str)
{
	size_t	equal_sign_pos;

	equal_sign_pos = 0;
	while (str[equal_sign_pos] && str[equal_sign_pos] != '=')
		++equal_sign_pos;
	if ('=' == str[equal_sign_pos])
		return (ft_strdup(str + equal_sign_pos + 1));
	else
		return (0);
}
