/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:15:13 by tredfort          #+#    #+#             */
/*   Updated: 2021/03/23 19:43:18 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <term.h>
#include <curses.h>
#define BUFFER_SIZE 1000

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int main(int argc, char **argv, char **env)
{
	char	line[BUFFER_SIZE];
	char	*tmp;
	char	*temp;
	int 	len;
	int		fd;
	struct	termios term;
	t_2list	*list;
	char	*file = "/Users/tredfort/.bash_history";
	char	*term_name = "xterm-256color";

	list = NULL;
	fd = init_history(file, &list);

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_name);
	tmp = ft_strdup("");
//	ft_2lstadd_front(&list, ft_2lstnew(tmp));
	while (strcmp(line, "\4"))
	{
		write(STDIN_FILENO, "minishell> ", 11);
		tputs(save_cursor, 1, ft_putchar);
		do
		{
			len = read(STDIN_FILENO, line, 100);
			line[len] = '\0';
			if (!strcmp(line, "\e[C") || !strcmp(line, "\e[D") || !strcmp(line, "\e[D"))
				continue;
			else if (!strcmp(line, "\e[A"))
			{
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				write(1, list->content, ft_strlen(list->content));
				temp = tmp;
				tmp = ft_strdup(list->content);
				free(temp);
				if (list->next)
					list = list->next;
			}
			else if (!strcmp(line, "\e[B"))
			{
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				write(1, list->content, ft_strlen(list->content));
				temp = tmp;
				tmp = ft_strdup(list->content);
				free(temp);
				if (list->prev)
					list = list->prev;
			}
			else if (!strcmp(line, "\177"))
			{
				tputs(cursor_left, 1, ft_putchar);
				tputs(delete_character, 1, ft_putchar);
				tmp[ft_strlen(tmp) - 1] = '\0';
			}
			else if (!strcmp(line, "\n"))
			{
				write(1, "\n", 1);
				if (ft_strlen(tmp) > 0)
				{
					ft_2lstadd_front(&list, ft_2lstnew(tmp));
					write(1, tmp, ft_strlen(tmp));
					write(1, "\n", 1);
				}
				temp = tmp;
				tmp = ft_strdup("");
				free(temp);
			}
			else
			{
				write(1, line, len);
				temp = tmp;
				tmp = ft_strjoin(tmp, line);
				free(temp);
			}
		} while (strcmp(line, "\n") && strcmp(line, "\4"));
	}
	return 0;
}
