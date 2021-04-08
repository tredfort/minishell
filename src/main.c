/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:15:13 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/08 23:36:52 by tredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	prompt(void)
{
	ft_putstr_fd("minishell> ", STDIN_FILENO);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_list	*lst;

	(void)argc;
	(void)argv;
	while (env)
	{
		prompt();
//		get_next_command(env, &line);
		get_next_line(0, &line);
		if (!lexer(line))
		{
			parser(line, &lst);
			print(lst);
//			executor(lst, env);
			ft_lstclear(&lst, free);
		}
		free(line);
	}
	return (0);
}
