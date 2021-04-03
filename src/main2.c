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
//	sh.env = parse_env(env);
	while (1)
	{
		ft_putstr_fd("minishell> ", STDIN_FILENO);
		get_next_line(STDIN_FILENO, &line);
		if (lexer(line))
			continue;
	 	else if (!strcmp(line, "\e[A"))
	 		printf("previous\n");
	 	else if (!strcmp(line, "\e[B"))
	 		printf("%d\n", printf("\e[B"));
	 	else
		{
	 		char **cmd_ar;
	 		cmd_ar = ft_split(line, ' ');
	 		ft_exec(*cmd_ar, cmd_ar);
	 		free(cmd_ar);
		}
		if (!ft_strcmp(line, "exxx"))
			return (0);
			print(split_into_commades(line));
		free(line);
	}
}
