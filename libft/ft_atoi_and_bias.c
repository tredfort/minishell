/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_and_bias.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 07:44:50 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/20 14:11:48 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_and_bias(char **str)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while (*(*str) && ((*(*str) >= '\t' && *(*str) <= '\r') || *(*str) == ' '))
		(*str)++;
	if (*(*str) == '-')
		sign = -1;
	if (*(*str) == '-' || *(*str) == '+')
		(*str)++;
	while (*(*str) && ft_isdigit(*(*str)))
		nb = nb * 10 + *(*str)++ - '0';
	return (sign * nb);
}
