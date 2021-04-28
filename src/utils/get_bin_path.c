/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smephest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 20:14:50 by smephest          #+#    #+#             */
/*   Updated: 2021/04/27 20:14:52 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char
	*get_bin_path(char *path, char *cmd)
{
	char		*bin_path;
	char		*bin_path_slash;

	if (path)
	{
		bin_path_slash = ft_strjoin(path, "/");
		bin_path = ft_strjoin(bin_path_slash, cmd);
		free(bin_path_slash);
	}
	else
		bin_path = ft_strdup(cmd);
	return (bin_path);
}
