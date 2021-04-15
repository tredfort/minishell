/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_and_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:02:20 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/15 13:02:22 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_and_free(char **s1, char *s2)
{
	char	*new;
	char	*tmp;

	tmp = *s1;
	new = ft_strjoin(*s1, s2);
	free(tmp);
	return (new);
}
