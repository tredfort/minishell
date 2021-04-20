/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:00:21 by tredfort          #+#    #+#             */
/*   Updated: 2020/11/06 20:27:08 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		count;

	count = 0;
	tmp = lst;
	if (tmp)
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
			count++;
		}
		if (tmp->next == NULL)
			count++;
	}
	return (count);
}
