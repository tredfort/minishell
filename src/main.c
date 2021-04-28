/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tredfort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:15:13 by tredfort          #+#    #+#             */
/*   Updated: 2021/04/28 22:28:23 by smephest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	prompt(void)
{
	ft_putstr_fd("\033[1;35mminishell> \033[0m", STDERR_FILENO);
}

void	sigint_handler(int sig_num)
{
	int	stat_loc;

	wait(&stat_loc);
	enable_basic_mode();
	if (stat_loc == sig_num)
	{
		if (sig_num == SIGINT)
			ft_putchar_fd('\n', 2);
		else if (sig_num == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
		g_mini.status = 128 + sig_num;
		g_mini.status_set = 1;
	}
}

void
	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	**envp;
	t_list	*lst;

	(void)argc;
	(void)argv;
	init_signals();
	envp = init_envp_with_default_variables(env);
	init_history(get_value(env, "HOME"));
	while (envp)
	{
		prompt();
		get_next_command(env, &line);
		g_mini.status_set = 0;
		if (line && !lexer(line))
		{
			lst = NULL;
			parser(line, &lst);
			string_formatting(lst, envp);
			ft_executor(lst, &envp);
			clear_command_list(lst);
		}
		free(line);
	}
	return (0);
}
