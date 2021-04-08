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
#define BUFFER_SIZE 1000

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	dir[BUFFER_SIZE];
	int		i;
	char	*error;

	sh = (t_sh){0};
//	sh.env_dict = parse_env(env);
	while (1)
	{
		ft_putstr_fd("minishell> ", STDIN_FILENO);
		get_next_line(STDIN_FILENO, &line);
		if (lexer(line))
			continue;
	 	else if (!ft_strncmp(line, "export ", 7))
			ft_export(ft_split(line + 7, ' '));
		else if (!ft_strncmp(line, "unset ", 6))
			ft_unset(ft_split(line + 6, ' '));
		else if (!ft_strncmp(line, "cd ", 3))
			ft_cd(ft_split(line + 3, ' '));
		else if (!strcmp(line, "pwd"))
	 		ft_pwd();
	 	else if (!strcmp(line, "env"))
	 		ft_env();
	 	else if (!ft_strncmp(line, "exit ", 5))
		{
			ft_exit(ft_split(line + 5, ' '));
			free(line);
			return (0);
		}
	 	else if (!ft_strncmp(line, "echo ", 5))
	 		ft_echo(ft_split(line + 5, ' '));
	 	else if (!strcmp(line, "\e[A"))
	 		printf("previous\n");
	 	else if (!strcmp(line, "\e[B"))
	 		printf("%d\n", printf("\e[B"));
	 	else
			print(split_into_commades(line));
		free(line);
	}
}
