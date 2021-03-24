#include "../../includes/minishell.h"

t_list
	*sort_list(t_list *list)
{
	t_list	*i;
	t_list	*j;
	void	*tmp;
	t_list *new_list;

	new_list = ft_lstmap(list, (void *(*)(void *))&create_dict_item, &del_dict_item);
	i = new_list;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->content,j->content) > 0)
			{
				tmp = i->content;
				i->content = j->content;
				j->content = tmp;
			}
			j = j->next;
		}
		i = i->next;
	}
	return new_list;
}

static void
	add_variables(char **argv)
{
	//TODO *argv or argv?
	while (*argv)
	{
		ft_lstadd_back(&sh.env_dict, ft_lstnew(*argv));
		++argv;
	}
}

void
	ft_export(char **argv)
{
	t_list	*sorted_list;
	t_list	*t;
	char	*key;
	char 	*value;

	if (!argv || !*argv)
	{
		sorted_list = sort_list(sh.env_dict);
		t = sorted_list;
		while (t)
		{
			ft_putstr_fd("declare -x ", 1);
			key = get_key_env_item(t->content);
			value = get_value_env_item(t->content);
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
			t = t->next;
		}
		free(sorted_list);
	}
	else
		add_variables(argv);
}