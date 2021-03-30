/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:42:56 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/01 18:43:02 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prompt(void)
{
	ft_putstr_fd("minishell> ", STDIN_FILENO);
}

char	after_space(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (*str);
}
