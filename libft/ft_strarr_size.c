/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:00:24 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/23 16:00:27 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strarr_size(char **str_arr)
{
	size_t	size;

	size = 0;
	while (str_arr && str_arr[size])
		++size;
	return (size);
}
