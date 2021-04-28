/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 05:55:59 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/28 22:31:21 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_putchar(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}

static void	enable_custom_mode(char *term_name)
{
	struct termios	user;

	tcgetattr(STDIN_FILENO, &g_mini.basic);
	tcgetattr(STDIN_FILENO, &user);
	user.c_lflag &= ~(ECHO);
	user.c_lflag &= ~(ISIG);
	user.c_lflag &= ~(ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &user);
	if (!term_name || !*term_name)
		term_name = getenv("TERM");
	if (!term_name || !*term_name)
		term_name = "xterm-256color";
	if (tgetent(STDIN_FILENO, term_name) < 1)
		exit(errno);
}

void	enable_basic_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_mini.basic);
}

void	get_next_command(char **env, char **line)
{
	char	*tmp;
	t_2list	*lst;

	lst = NULL;
	tmp = NULL;
	enable_custom_mode(get_value(env, "TERM"));
	tputs(save_cursor, 1, my_putchar);
	*line = ft_strdup("");
	input_cycle(line, &tmp, lst);
	if (*line && (*line)[0] == '#')
	{
		free(*line);
		*line = NULL;
	}
	if (tmp)
		free(tmp);
	enable_basic_mode();
}
