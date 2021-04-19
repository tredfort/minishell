/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:18:54 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/19 17:34:44 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	backspace(char *line)
{
	int	line_len;

	line_len = ft_strlen(line);
	if (line_len > 0)
	{
		if (line[line_len - 1] < 0)
			line_len -= 1;
		line[line_len - 1] = '\0';
		tputs(cursor_left, 1, my_putchar);
		tputs(tigetstr("ed"), 1, my_putchar);
	}
	else
		sound_signal();
}

static int	interrupt_signal(char **line)
{
	write(STDIN_FILENO, "\n", 1);
	free(*line);
	*line = NULL;
	return (1);
}

static void	end_of_file(char *line)
{
	if (!ft_strlen(line))
	{
		ft_putendl_fd("exit", STDIN_FILENO);
		ft_exit(NULL);
	}
	else
		sound_signal();
}

static int	new_line(char **line, t_2list **head)
{
	write(STDIN_FILENO, "\n", 1);
	if (ft_strlen(*line))
		ft_2lstadd_front(head, ft_2lstnew(*line));
	else
	{
		free(*line);
		*line = NULL;
	}
	return (1);
}

void	input_cycle(char **line, char **tmp, t_2list **head, t_2list *item)
{
	char	buf[SHELL_BUFFER + 1];
	int		len;

	while (1)
	{
		len = read(STDIN_FILENO, buf, SHELL_BUFFER);
		buf[len] = '\0';
		if (*buf == '\n' && new_line(line, head))
			break ;
		else if (*buf == '\3' && interrupt_signal(line))
			break ;
		else if (*buf == '\4')
			end_of_file(*line);
		else if (!ft_strcmp(buf, "\e[A"))
			previous_command(&item, *head, tmp, line);
		else if (!ft_strcmp(buf, "\e[B"))
			next_command(&item, tmp, line);
		else if (!ft_strcmp(buf, "\177"))
			backspace(*line);
		else if ((*buf > 0 && *buf < 32) || *buf == 127)
			continue ;
		else
			add_buffer(line, buf);
	}
}
