/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerror_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:30:28 by smephest          #+#    #+#             */
/*   Updated: 2021/04/26 23:30:29 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void
	ft_strerror_fd(char *str_error, char *cmd, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	if (cmd)
	{
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putendl_fd(str_error, fd);
}
