/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:25:36 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/19 17:36:32 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_strdup_and_free(char **old_str, char *new_str)
{
	char	*tmp;

	tmp = *old_str;
	*old_str = ft_strdup(new_str);
	free(tmp);
}

void	sound_signal(void)
{
	write(STDERR_FILENO, "\a", 1);
}

void	previous_command(t_2list **lst, char **tmp, char **line)
{
	if ((*lst && !(*lst)->next) || !g_mini.lst)
		sound_signal();
	else if (g_mini.lst)
	{
		tputs(restore_cursor, 1, my_putchar);
		tputs(tigetstr("ed"), 1, my_putchar);
		if (!*lst)
		{
			*tmp = ft_strdup(*line);
			*lst = g_mini.lst;
		}
		else
			*lst = (*lst)->next;
		ft_strdup_and_free(line, (*lst)->content);
		ft_putstr_fd(*line, STDOUT_FILENO);
	}
}

void	next_command(t_2list **lst, char **tmp, char **line)
{
	if (!*lst)
		sound_signal();
	else
	{
		tputs(restore_cursor, 1, my_putchar);
		tputs(tigetstr("ed"), 1, my_putchar);
		*lst = (*lst)->prev;
		if (!*lst)
		{
			ft_strdup_and_free(line, *tmp);
			free(*tmp);
			*tmp = NULL;
		}
		else
			ft_strdup_and_free(line, (*lst)->content);
		ft_putstr_fd(*line, STDOUT_FILENO);
	}
}

void	add_buffer(char **line, char *buf)
{
	ft_putstr_fd(buf, STDIN_FILENO);
	*line = ft_strjoin_and_free(line, buf);
}
