#include "../../includes/minishell.h"

char	*increase_sh_level(char *value)
{
	char	*number;
	char	*shlvl;
	int 	i;
	int		level;

	i = -1;
	if (!*value)
		return (ft_strdup("SHLVL="));
	while (value[++i])
	{
		if (!ft_isdigit(value[i]))
			return (ft_strdup("SHLVL=1"));
	}
	level = ft_atoi(value);
	if (level >= 999)
		return (ft_strdup("SHLVL="));
	number = ft_itoa(++level);
	shlvl = ft_strjoin("SHLVL=", number);
	free(number);
	return (shlvl);
}

void	add_default_variables(char ***envp)
{
	char	**tmp_arr;
	char	*tmp_str;

	tmp_arr = ft_calloc(4, sizeof(char *));
	tmp_arr[0] = ft_strdup("OLDPWD");
	tmp_str = getcwd(NULL, 0);
	tmp_arr[1] = ft_strjoin("PWD=", tmp_str);
	tmp_arr[2] = increase_sh_level(get_value(*envp, "SHLVL"));
	add_variables(tmp_arr, envp);
	free(tmp_str);
	free(tmp_arr[0]);
	free(tmp_arr[1]);
	free(tmp_arr[2]);
	free(tmp_arr[3]);
	free(tmp_arr);
}

char	**init_envp(char **env)
{
	char	**envp;
	int		i;

	envp = ft_calloc(ft_strarr_size(env) + 1, sizeof(char *));
	if (!envp)
		exit(errno);
	i = -1;
	while(env && env[++i])
			envp[i] = ft_strdup(env[i]);
	return (envp);
}

char	**init_envp_with_default_variables(char **env)
{
	char	**my_envp;

	my_envp = init_envp(env);
	add_default_variables(&my_envp);
	return (my_envp);
}