/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_call_execve.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:43:05 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:43:06 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	err_exit(char *msg, int exit_code, t_command *data, t_env *env);

void	call_execve(t_command *data, t_env *env)
{
	if (!data->args || !data->args[0])
		err_exit("command not found", 127, data, env);
	if (!data->args[0][0])
		exit(0);
	execve(data->args[0], data->args, env->env);
	if (ft_strchr(data->args[0], '/'))
	{
		if (errno == ENOENT)
			err_exit("No such file or directory", 127, data, env);
		else if (errno == EISDIR)
			err_exit("IS a directory", 126, data, env);
		else if (errno == EACCES)
			err_exit("Permission denied", 126, data, env);
		else
			err_exit(strerror(errno), 1, data, env);
	}
	else
		err_exit("command not found", 127, data, env);
}

static void	err_exit(char *msg, int exit_code, t_command *data, t_env *env)
{
	print_err(ft_get("SHELL", env->env), msg, data->args[0]);
	exit(exit_code);
}
