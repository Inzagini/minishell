#include "minishell.h"

void	print_export(t_env	*env);
void	sort_export(t_env *env);
int		check_options(char **args);
int		check_argument(char *arg);
int		find_argument(char *var, char **env);
int		append_to_end(char *var, char **list);
char	*add_quotes(char *arg);
int		export_to_exp(char *arg, t_env *env);
int		export_to_env(char *arg, t_env *env);


void	ft_export(t_command *cmd, t_env *env)
{
	int		i;

	if (cmd->args[1] == 0)
		print_export(env);
	i = check_options(cmd->args);
	if (i > 0)
	{
		printf("%s: export: %.2s: invalid option\n", getenv("SHELL"), cmd->args[i]);  // need to define path, set error message etc.
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
			if (export_to_exp(cmd->args[i], env) == 1 || export_to_env(cmd->args[i], env) == 1)
				return ;
		}
	}
}

int	export_to_env(char *arg, t_env *env)
{
	int		j;
	char	*new_env;

	if (ft_strchr(arg, '='))
	{
		j = find_argument(arg, env->env_current);
		new_env = ft_strdup(arg);
		if (!new_env)
			return (1); //needs some exit/cleaning
		if (j >= 0)
		{
			free (env->env_current[j]);
			env->env_current[j] = new_env;
		}
		else
			if (append_to_end(new_env, env->env_current) == 1)
				return (1);	//need some exit/cleaning
	}
	return (0);
}

int	export_to_exp(char *arg, t_env *env)
{
	int		j;
	char	*new_exp;

	j = find_argument(arg, env->export_current);
	if (ft_strchr(arg, '='))
	{
		new_exp = add_quotes(arg);
		if (!new_exp)
			return (1);//exit and clean
	}
	else if (j == -1)
	{
		new_exp = ft_strdup(arg);
		if (!new_exp)
			return (1);//exit and clean
	}
	if (j >= 0 && ft_strchr(arg, '='))
	{
		free (env->export_current[j]);
		env->export_current[j] = new_exp;
	}
	if (j == -1)
		if (append_to_end(new_exp, env->export_current) == 1)
			return (1);	//need some exit/cleaninh
	return (0);
}

char	*add_quotes(char *arg)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc((ft_strlen(arg) + 3) * sizeof(char));
	if (!new)
		return (NULL);
	while (arg[i] && arg[i] != '=')
	{
		new[i] = arg[i];
		i++;
	}
	new[i++] = '=';
	new[i++] = '"';
	while (arg[i - 1])
	{
		new[i] = arg[i - 1];
		i++;
	}
	new[i] = '"';
	new[i + 1] = '\0';
	return (new);
}

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
