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
#define BUFFER_SIZE 1000

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	dir[BUFFER_SIZE];
	int		i;

	while (1)
	{
		write(STDIN_FILENO, "minishell> ", 11);
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
	 	else if (!strcmp(line, "echo"))
	 	{
	 		printf("%s\n", line + 5);
	 		free(line);
	 	}
	 	else if (!strcmp(line, "\e[A"))
	 	{
	 		printf("previous\n");
	 		free(line);
	 	}
	 	else if (!strcmp(line, "\e[B"))
	 	{
	 		printf("%d\n", printf("\e[B"));
	 		free(line);
	 	}
	 	else
	 	{
	 		printf("%s\n", line);
	 		free(line);
	 	}
	}
}
