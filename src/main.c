/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:15:13 by tredfort          #+#    #+#             */
/*   Updated: 2021/03/16 21:55:40 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <term.h>
#define BUFFER_SIZE 100

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	dir[BUFFER_SIZE];
	int 	i;
	struct termios term;

//	tcgetattr(0, &term);
//	term.c_lflag &= ~(ECHO);
//	tcsetattr(0, TCSANOW, &term);
	while (1)
	{
		write(0, "bash-3.2$ ", 10);
		get_next_line(STDIN_FILENO, &line);
		if (!strcmp(line, "pwd"))
		{
			getcwd(dir, BUFFER_SIZE);
			printf("%s\n", dir);
			free(line);
		}
		else if (!strcmp(line, "env"))
		{
			i = 0;
			while (env[i])
				printf("%s\n", env[i++]);
			free(line);
		}
		else if (!strcmp(line, "exit"))
		{
			printf("exit\n");
			free(line);
			return 0;
		}
		else if (!strncmp(line, "echo", 4))
		{
			printf("%s\n", line + 5);
			free(line);
		}
		else
		{
			printf("%s\n", line);
			free(line);
		}
	}
}
