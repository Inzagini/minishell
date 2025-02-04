/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:42:59 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:43:00 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_variable(char *arg, char **array);
int		check_options_unset(char **args);

void	ft_unset(t_command *cmd, t_env *env)
{
	int		i;

	if (cmd->args[1] == 0)
		return ;
	i = check_options_unset(cmd->args);
	if (i > 0)
	{
		print_err(ft_get("SHELL", env->env), "unset", "invalid option");
		print_err(NULL, "unset: usage: unset [name ...]", NULL);
		env->last_exit_status = 2;
		return ;
	}
	while (cmd->args[++i])
	{
		unset_variable(cmd->args[i], env->env);
		unset_variable(cmd->args[i], env->exp);
	}
}

void	unset_variable(char *arg, char **array)
{
	int	i;
	int	len;

	if (!array || !array[0] || !arg)
		return ;
	i = -1;
	len = ft_strlen(arg);
	while (array[++i])
	{
		if (ft_strncmp(array[i], arg, len) == 0
			&& (array[i][len] == '\0'
			|| array[i][len] == '='))
		{
			free (array[i]);
			while (array[i + 1])
			{
				array[i] = array[i + 1];
				i++;
			}
			array[i] = 0;
		}
	}
}

int	check_options_unset(char **args)
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
