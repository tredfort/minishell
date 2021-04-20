/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:51:03 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/20 14:46:36 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_substr(char const *s, char c)
{
	int		count;

	count = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

static char	**ft_free(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		size;
	int		i;

	if (!s)
		return (NULL);
	arr = (char **)ft_calloc(sizeof(char *), (count_substr(s, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		size = 0;
		while (*s && *s == c)
			s++;
		while (*s && *s != c && s++)
			size++;
		if (size)
		{
			arr[i] = ft_substr((char *)(s - size), 0, size);
			if (!arr[i++])
				return (ft_free(arr, i - 2));
		}
	}
	return (arr);
}
