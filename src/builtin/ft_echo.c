#include "../../includes/minishell.h"

int
	is_n_flag(char *str)
{
	int	i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		++i;
	}
	return (1);
}

/*
** echo function
** if has flag -n in the beginning the don't show new line
*/

void
	ft_echo(char **argv)
{
	int	i;
	int	flag_n;

	i = 0;
	flag_n = 0;
	g_mini.status = 0;
	while (argv[i] && is_n_flag(argv[i]))
	{
		flag_n = 1;
		++i;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd(' ', 1);
		++i;
	}
	if (!flag_n)
		ft_putchar_fd('\n', 1);
}
