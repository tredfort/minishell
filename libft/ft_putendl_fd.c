/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:18:48 by tredfort          #+#    #+#             */
/*   Updated: 2020/11/02 14:22:00 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	*str;

	if (s)
	{
		str = ft_substr(s, 0, ft_strlen(s) + 1);
		str[ft_strlen(str)] = '\n';
		ft_putstr_fd(str, fd);
		free(str);
	}
}
