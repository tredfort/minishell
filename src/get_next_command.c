/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 05:55:59 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/08 05:56:08 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_putchar(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}

static void	enable_custom_mode(t_term *term, char *term_name)
{
	tcgetattr(STDIN_FILENO, &term->basic);
	tcgetattr(STDIN_FILENO, &term->user);
	term->user.c_lflag &= ~(ECHO);
	term->user.c_lflag &= ~(ISIG);
	term->user.c_lflag &= ~(ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &term->user);
	if (!term_name)
		term_name = getenv("TERM");
	if (!term_name)
		term_name = "xterm-256color";
	if (tgetent(STDIN_FILENO, term_name) < 1)
		exit(1);
}

static void	enable_basic_mode(t_term *term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &term->basic);
}

void	get_next_command(char **env, char **line, t_2list **head)
{
	t_term	term;
	char	*tmp;
	t_2list	*item;

	tmp = NULL;
	item = NULL;
	enable_custom_mode(&term, get_value(env, "TERM"));
	tputs(save_cursor, 1, my_putchar);
	*line = ft_strdup("");
	input_cycle(line, &tmp, head, item);
	if (*line && (*line)[0] == '#')
	{
		free(*line);
		*line = NULL;
	}
	if (tmp)
		free(tmp);
	enable_basic_mode(&term);
}
