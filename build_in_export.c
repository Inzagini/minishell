#include "minishell.h"

void	print_export(t_env	*env);
void	sort_export(t_env *env);
int		check_options(char **args);
int		check_argument(char *arg);
int		find_argument(char *var, char **env);
int		append_to_end(char *var, char **list);


void	ft_export(t_command *cmd, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	if (cmd->args[1] == 0)
		print_export(env);
	i = check_options(cmd->args);
	if (i > 0)
	{
		printf("%s: export: %s: invalid option\n", getenv("SHELL"), cmd->args[i]);  // need to define path, set error message etc.
		printf("export: usage: export [name[=value] ...]\n");
		env->last_exit_status = 2;
		return ;
	}
	while (cmd->args[++i])
	{
		if (check_argument(cmd->args[i]) == 1)
		{
			printf("%s: export: `%s': not a valid identifier\n", getenv("SHELL"), cmd->args[i]);
			env->last_exit_status = 1;
		}
		else
		{
			j = find_argument(cmd->args[i], env->export_current);
			if (j >= 0)
			{
				if (ft_strchr(cmd->args[i], '='))
				{
					free (env->export_current[j]);
					env->export_current[j] = ft_strdup(cmd->args[i]); // ALSO NEED TO UPDATE IN ENVIRON LIST
					if (!env->export_current[j])
						return ;		//need some exit/cleaning
				}
			}
			else
			{
				append_to_end(cmd->args[i], env->export_current);
//				if (ft_strchr(cmd->args[i], '='))
//					append_to_end(env->export_current, env->env_current);
				// if '= sign', append to both export and env list
			}
		}
	}
}

int	append_to_end(char *var, char **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	free (list[i]);
	list[i] = ft_strdup(var);
	if (!list[i])
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
	int	i;

	i = -1;
	sort_export(env);
	while (env->export_current[++i])
		printf("declare -x %s\n", env->export_current[i]);
}

void	sort_export(t_env *env)
{
	char	*temp;
	int		i;

	i = 0;
	while (env->export_current[i] && env->export_current[i + 1])
	{
		if (ft_strncmp(env->export_current[i], env->export_current[i + 1], 1024) > 0)
		{
			temp = env->export_current[i];
			env->export_current[i] = env->export_current[i + 1];
			env->export_current[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}
