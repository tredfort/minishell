/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:51:51 by tredfort          #+#    #+#             */
/*   Updated: 2020/11/07 19:01:04 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	const char	*odst;
	const char	*osrc;
	size_t		size;
	size_t		dstlen;

	odst = dst;
	osrc = src;
	size = dstsize;
	while (size-- != 0 && *dst != '\0')
		dst++;
	dstlen = dst - odst;
	size = dstsize - dstlen;
	if (size-- == 0)
		return (dstlen + ft_strlen(src));
	while (*src != '\0')
	{
		if (size != 0)
		{
			*dst++ = *src;
			size--;
		}
		src++;
	}
	*dst = '\0';
	return (dstlen + (src - osrc));
}
