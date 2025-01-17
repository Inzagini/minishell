#include "minishell.h"

int	append_to_end(char *var, char **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	free (list[i]);
	list[i] = var;
	list[i + 1] = malloc(1 * sizeof (char *));
	if (!list[i + 1])
		return (1);
	list[i + 1] = 0;
	return (0);
}

int	find_argument(char *var, char **env)
{
	size_t	len_var;
	size_t	i;
	char	*end;
	char	*env_eq;

	i = -1;
	end = ft_strchr(var, '=');
	if (end != NULL)
		len_var = end - var;
	else
		len_var = ft_strlen(var);
	while (env[++i])
	{
		env_eq = ft_strchr(env[i], '=');
		if (env_eq != NULL)
		{
			if (ft_strncmp(env[i], var, len_var) == 0 && env[i][len_var] == '=')
				return (i);
		}
		else
			if (ft_strncmp(env[i], var, len_var) == 0)
				return (i);
	}
	return (-1);
}

int	check_argument(char *arg)
{
	size_t	i;
	size_t	j;
	char	*ok;

	ok = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	i = 0;
	if (arg[0] >= '0' && arg[0] <= '9')
		return (1);
	while (arg[i])
	{
		j = 0;
		if (i > 0 && arg[i] == '=')
			break ;
		while (ok[j])
		{
			if (arg[i] == ok[j])
				break ;
			j++;
		}
		if (j == 63)
			return (1);
		i++;
	}
	return (0);
}

int	check_options(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '-')
			return (i);
	}
	return (0);
}

void	print_export(t_env *env)
{
	int		i;
	char	*temp;
	i = 0;
	while (env->export_current[i] && env->export_current[i + 1])
	{
		if (ft_strncmp(env->export_current[i]
				, env->export_current[i + 1], 1024) > 0)
		{
			temp = env->export_current[i];
			env->export_current[i] = env->export_current[i + 1];
			env->export_current[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	i = -1;
	while (env->export_current[++i])
		printf("declare -x %s\n", env->export_current[i]);
}
