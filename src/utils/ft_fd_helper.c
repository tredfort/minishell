/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 22:21:28 by smephest          #+#    #+#             */
/*   Updated: 2021/04/28 22:21:30 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int
	init_fd_arr(int *init_fd)
{
	init_fd[0] = dup(0);
	init_fd[1] = dup(1);
	return (1);
}

void
	replace_fd_back(int *init_fd)
{
	dup2(init_fd[0], 0);
	dup2(init_fd[1], 1);
	close(init_fd[0]);
	close(init_fd[1]);
}

void
	crutch(int *redir_flag)
{
	*redir_flag = -1;
	g_mini.status = 1;
}
