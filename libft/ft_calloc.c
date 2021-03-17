/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:17:54 by tredfort          #+#    #+#             */
/*   Updated: 2020/11/02 11:20:27 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*new;
	size_t	total;
	size_t	i;

	i = 0;
	total = size * count;
	if (!(new = malloc(total)))
		return (0);
	while (total-- > 0)
	{
		new[i] = 0;
		i++;
	}
	return ((void *)new);
}
