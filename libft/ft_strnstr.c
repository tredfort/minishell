/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:53:41 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/20 14:39:38 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	i;
	size_t	j;

	if (!str)
		return (0);
	if (!*find)
		return ((char *)str);
	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == find[0])
		{
			j = 1;
			while (find[j] && str[i + j] == find[j] && i + j < len)
				j++;
			if (!find[j])
				return ((char *)(str + i));
		}
		i++;
	}
	return (0);
}
