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
	char	*error;

	while (1)
	{
		ft_putstr_fd("minishell> ", STDIN_FILENO);
		get_next_line(STDIN_FILENO, &line);
		error = syntax_analysis(line);
		if (error)
			ft_putstr_fd(error, STDIN_FILENO);
//		{
//			ft_putstr_fd("minishell: ", STDIN_FILENO);
//			if (errno == 1)
//				ft_putstr_fd("syntax error near unexpected token `;;'\n",
//			STDIN_FILENO);
//			else if (errno == 2)
//				ft_putstr_fd("syntax error near unexpected token `)'\n",
//							 STDIN_FILENO);
//			else if (errno == 3)
//				ft_putstr_fd("syntax error near unexpected token `<'\n",
//							 STDIN_FILENO);
//			else if (errno == 4)
//				ft_putstr_fd("syntax error near unexpected token `|'\n",
//							 STDIN_FILENO);
//		}
//		else if (errno < 0)
//			continue;
	 	else if (!strcmp(line, "pwd"))
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
