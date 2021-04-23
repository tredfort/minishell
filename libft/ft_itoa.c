/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:59:50 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/22 22:14:13 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_number(unsigned int nb)
{
	int		size;

	size = 1;
	while (nb > 9)
	{
		size++;
		nb /= 10;
	}
	return (size);
}

char 	*ft_itoa(int n)
{
	char			*number;
	unsigned int	nb;
	unsigned int	size;
	unsigned int	i;

	if (n < 0)
		nb = (unsigned int)(-1 * n);
	else
		nb = (unsigned int)n;
	size = size_number(nb);
	number = (char *)malloc(sizeof(char) * (size + 1 + (int)(n < 0)));
	if (!number)
		return (NULL);
	i = 0;
	if (n < 0 && ++i)
		number[0] = '-';
	i += size;
	number[i] = '\0';
	while (size-- > 0)
	{
		i--;
		number[i] = (nb % 10) + '0';
		nb /= 10;
	}
	return (number);
}
