/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:17:54 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/20 14:13:02 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*new;
	size_t	total;
	size_t	i;

	i = 0;
	total = size * count;
	new = malloc(total);
	if (!new)
		return (0);
	while (total-- > 0)
	{
		new[i] = 0;
		i++;
	}
	return ((void *)new);
}
