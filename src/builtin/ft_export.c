#include "../../includes/minishell.h"

char
	**sort_argv(char **argv)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	char	**sort_argv;


	sort_argv = parse_env(argv);
	i = 0;
	while (sort_argv[i])
	{
		j = i + 1;
		while (sort_argv[j])
		{
			if (ft_strcmp(sort_argv[i], sort_argv[j]) > 0)
			{
				tmp = sort_argv[i];
				sort_argv[i] = sort_argv[j];
				sort_argv[j] = tmp;
			}
			++j;
		}
		++i;
	}
	return sort_argv;
}

static void
	add_variables(char **argv, char ***envp)
{
	size_t	size;
	char	**new_argv;
	size_t	i;

	size = ft_strarr_size(argv) + ft_strarr_size(*envp);
	new_argv = ft_calloc(size + 1, sizeof(char*));
	i = 0;
	while (*envp && (*envp)[i])
	{
		new_argv[i] = ft_strdup((*envp)[i]);
		++i;
	}
	while (argv && *argv)
	{
		new_argv[i] = ft_strdup(*argv);
		++argv;
		++i;
	}
	//TODO:: do we need free all str inside of array?
	free(*envp);
	//TODO::check if added var on first place
	*envp = new_argv;
}

void
	ft_export(char **argv, char ***envp)
{
	char	**sorted_list;
	char	**t;
	char	*key;
	char 	*value;

	if (!argv || !*argv)
	{
		sorted_list = sort_argv(*envp);
		t = sorted_list;
		while (t && *t)
		{
			ft_putstr_fd("declare -x ", 1);
			key = get_key_env_item(*t);
			value = get_value_env_item(*t);
			ft_putstr_fd(key, 1);
			if (value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(value, 1);
				ft_putstr_fd("\"", 1);
				free(value);
			}
			if (key)
				free(key);
			ft_putchar_fd('\n', 1);
			++t;
		}
		free(sorted_list);
	}
	else
		add_variables(argv, envp);
}