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
	char	**envp;
	t_list	*lst;
	t_2list	*history;
	t_sh	*temp;

	(void)argc;
	(void)argv;
	envp = parse_env(env);
	bash_history = init_history(get_value(env, "HOME"), &history);
	while (envp)
	{
		prompt();
		get_next_command(env, &line, &history);
//		get_next_line(STDIN_FILENO, &line);
		if (line && !lexer(line))
		{
			lst = NULL;
			parser(line, &lst);
			string_formatting(lst, envp);
			temp = lst->content;
			if (temp->argv)
			{
//				printf("tmp = %s\n", temp->argv[0]);
				ft_exec(temp->argv[0], temp->argv, &envp);
			}
//			print(lst);
//			executor(lst, env);
//			ft_lstclear(&lst, free);
			clear_command_list(lst);
		}
//		free(line);
	}
	return (0);
}
