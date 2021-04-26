/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:26:33 by smephest          #+#    #+#             */
/*   Updated: 2021/04/26 23:26:46 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int
	validate_var(char *str)
{
	if (!str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	++str;
	while (str && *str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		++str;
	}
	return (1);
}
