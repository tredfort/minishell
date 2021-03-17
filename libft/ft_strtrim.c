/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:20:28 by tredfort          #+#    #+#             */
/*   Updated: 2020/11/20 11:40:14 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;

	if (!s1 || !set)
		return (0);
	start = 0;
	while (s1[start] && (ft_strchr(set, s1[start])))
		start++;
	end = ft_strlen(s1);
	while (s1[start] && s1[end - 1] && (ft_strchr(set, s1[end - 1])))
		end--;
	return (ft_substr(s1, start, (end - start)));
}
