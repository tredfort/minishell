/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:33:19 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/19 17:33:23 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define BUFFER_SIZE 42

static char	*residue_handling(char *residue, char **line)
{
	char	*ptr_n;

	ptr_n = NULL;
	if (residue)
	{
		ptr_n = ft_strchr(residue, '\n');
		if (ptr_n)
		{
			*ptr_n++ = '\0';
			*line = ft_strdup(residue);
			ft_strcpy(residue, ptr_n);
		}
		else
		{
			*line = ft_strdup(residue);
			free(residue);
		}
	}
	else
		*line = ft_strdup("");
	return (ptr_n);
}

int	get_next_line(int fd, char **line)
{
	static char	*residue = NULL;
	char		buf[BUFFER_SIZE + 1];
	char		*ptr_n;
	size_t		rs;

	if (fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	ptr_n = residue_handling(residue, line);
	rs = 1;
	while (!ptr_n && rs > 0)
	{
		rs = read(fd, buf, BUFFER_SIZE);
		buf[rs] = '\0';
		ptr_n = ft_strchr(buf, '\n');
		if (ptr_n)
		{
			*ptr_n++ = '\0';
			residue = ft_strdup(ptr_n);
		}
		*line = ft_strjoin_and_free(line, buf);
	}
	if (ptr_n)
		return (1);
	residue = NULL;
	return (0);
}
