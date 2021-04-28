/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:34:53 by smephest          #+#    #+#             */
/*   Updated: 2021/04/28 22:27:14 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_numeric_argument(char *str)
{
	while (*str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void
	save_and_exit(int status)
{
	save_history();
	exit(status);
}

void	ft_exit(char **args)
{
	char	*error_msg;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (args && args[0])
	{
		if (!is_numeric_argument(args[0]))
		{
			error_msg = ft_strjoin(args[0], ": numeric argument required");
			ft_strerror(error_msg, "exit");
			free(error_msg);
			save_and_exit(255);
		}
		if (!args[1])
			save_and_exit((unsigned char)ft_atoi(args[0]));
		ft_strerror("too many arguments", "exit");
		g_mini.status = 1;
	}
	else
		save_and_exit(0);
}
