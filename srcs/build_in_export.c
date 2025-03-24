/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:42:56 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:42:57 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_command *cmd, t_env *env)
{
	int	i;

	if (cmd->args[1] == 0)
		print_export(env);
	i = check_options(cmd->args);
	if (i > 0)
	{
		print_err_long(ft_get("SHELL", env->env),
			"export", cmd->args[i], "invalid option");
		print_err_long("export", "usage", "export [name[=value] ...]", NULL);
		env->last_exit_status = 2;
		return ;
	}
	check_add_vars(cmd, env, i);
}

void	check_add_vars(t_command *cmd, t_env *env, int i)
{
	while (cmd->args[++i])
	{
		if (check_argument(cmd->args[i]) == 1)
		{
			print_err_long(ft_get("SHELL", env->env),
				"export", cmd->args[i], "not a valid identifier");
			env->last_exit_status = 1;
		}
		else
		{
			if (export_to_exp(cmd->args[i], env) == 1
				|| export_to_env(cmd->args[i], env) == 1)
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
		j = find_argument(arg, env->env);
		new_env = ft_strdup(arg);
		if (!new_env)
			return (1);
		if (j >= 0)
		{
			free (env->env[j]);
			env->env[j] = new_env;
		}
		else
			if (append_to_end(new_env, &env->env) == 1)
				return (1);
	}
	return (0);
}

int	export_to_exp(char *arg, t_env *env)
{
	int		j;
	char	*new_exp;

	j = find_argument(arg, env->exp);
	if (ft_strchr(arg, '='))
	{
		new_exp = add_quotes(arg);
		if (!new_exp)
			return (1);
	}
	else if (j == -1)
	{
		new_exp = ft_strdup(arg);
		if (!new_exp)
			return (1);
	}
	if (j >= 0 && ft_strchr(arg, '='))
	{
		free (env->exp[j]);
		env->exp[j] = new_exp;
	}
	if (j == -1)
		if (append_to_end(new_exp, &env->exp) == 1)
			return (1);
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
