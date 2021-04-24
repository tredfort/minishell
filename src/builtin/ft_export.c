#include "../../includes/minishell.h"

char
	**sort_argv(char **argv)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	char	**sort_argv;

	sort_argv = shall_copy_env(argv);
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

void
	add_variables(char **argv, char ***envp)
{
	size_t	i;
	char 	*error;
	char 	*error_left;

	i = 0;
	while (argv && argv[i])
	{
		if (validate_var(get_key_env_item(argv[i])))
			add_var(argv[i], envp);
		else
		{
			error_left = ft_strjoin("`", argv[i]);
			error = ft_strjoin(error_left, "': not a valid identifier");
			ft_strerror_fd(error, "export", 2);
			free(error_left);
			free(error);
		}
		++i;
	}
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
		printf("show export\n");
		sorted_list = sort_argv(*envp);
		printf("list sorted\n");
		t = sorted_list;
		while (t && *t)
		{
			key = get_key_env_item(*t);
			value = get_value_env_item(*t);
			ft_putstr_fd("declare -x ", 1);
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