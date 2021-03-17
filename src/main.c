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

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 100

int main(int argc, char **argv, char **env)
{
	char	b;
	char	buffeer[BUFFER_SIZE];
	char	dir[BUFFER_SIZE];
	int 	i;

	while (1)
	{
		write(0, "bash-3.2$ ", 10);
		i = 0;
		while (read(0, &b, 1) && b != '\n')
			buffeer[i++] = b;
		//comment two
		buffeer[i] = '\0';
		//comment
		if (!strcmp(buffeer, "pwd"))
		{
			getcwd(dir, BUFFER_SIZE);
			write(0, dir, strlen(dir));
			write(1, "\n", 1);
		}
		else if (!strcmp(buffeer, "env"))
		{
			i = 0;
			while (env[i])
				printf("%s\n", env[i++]);
		}
		else if (!strcmp(buffeer, "exit"))
			exit(0);
	}
	return 0;
}
