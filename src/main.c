/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:15:13 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/08 05:35:29 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	prompt(void)
{
	ft_putstr_fd("minishell> ", STDIN_FILENO);
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	t_list	*cmd;

	(void)argc;
	(void)argv;
	cmd = NULL;
	while (1)
	{
		prompt();
//		get_next_command(env, &line);
		get_next_line(1, &line);
		if (!lexer(line))
		{
			ft_putendl_fd(line, STDIN_FILENO);
//			parser(line, cmd);
//			executor(cmd, env);
		}
		free(line);
	}
	return (0);
}