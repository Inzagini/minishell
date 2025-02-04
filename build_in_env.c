/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:42:34 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:42:35 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env);

void	ft_env(t_command *cmd, t_env *env)
{
	if (cmd->args[1] != 0)
	{
		print_err(ft_get("SHELL", env->env),
			"env: only supported without options/arguments\n", NULL);
		env->last_exit_status = 1;
	}
	else
		print_env(env);
}

void	print_env(t_env *env)
{
	int	i;

	i = -1;
	while (env->env[++i])
		printf("%s\n", env->env[i]);
}
