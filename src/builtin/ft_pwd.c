/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:35:14 by smephest          #+#    #+#             */
/*   Updated: 2021/04/26 23:35:43 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char	*res;

	res = getcwd(NULL, 0);
	ft_putendl_fd(res, STDOUT_FILENO);
	free(res);
}
