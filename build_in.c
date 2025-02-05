/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quannguy <quannguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:43:03 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/05 15:51:48 by quannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pre_handle(t_command *cmd, t_exdat *data, t_env *env);
static void	reset_fds(int origin_in, int origin_out);

void	execute_build_in(t_command *cmd, t_env *env,
	t_exdat *data, t_command *head)
{
	data->origin_in = dup(STDIN_FILENO);
	data->origin_out = dup(STDOUT_FILENO);
	close(data->pipefd[0][0]);
	if (executor_init(data))
		return ;
	if (pipe(data->pipefd[1]) == -1)
	{
		close(*(data->pipefd)[0]);
		return ;
	}
	if (pre_handle(cmd, data, env))
	{
		env->last_exit_status = 1;
		reset_fds(data->origin_in, data->origin_out);
		return ;
	}
	close(data->pipefd[1 - ((cmd->id + 1) % 2)][1]);
	call_builtin(cmd, env, data, head);
	reset_fds(data->origin_in, data->origin_out);
}

void	call_builtin(t_command *cmd, t_env *env,
	t_exdat *data, t_command *head)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd(env);
	else if (!ft_strcmp(cmd->args[0], "export"))
		ft_export(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		ft_unset(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "env"))
		ft_env(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(cmd, env, head, data);
}

static int	pre_handle(t_command *cmd, t_exdat *data, t_env *env)
{
	if (redirect_in_handle(cmd, data, env))
		return (close_child_pipes(cmd, data->pipefd), 1);
	if (redirect_out_handle(cmd, data, env))
		return (close_child_pipes(cmd, data->pipefd), 1);
	close_child_pipes(cmd, data->pipefd);
	return (0);
}

static void	reset_fds(int origin_in, int origin_out)
{
	if (origin_in != -1)
	{
		if (dup2(origin_in, STDIN_FILENO) == -1)
			perror("dup2:");
		close(origin_in);
	}
	if (origin_out != -1)
	{
		if (dup2(origin_out, STDOUT_FILENO) == -1)
			perror("dup2:");
		close(origin_out);
	}
}
