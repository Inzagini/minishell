/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:43:08 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:43:09 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pre_handle(t_command *cmd, t_exdat *data, t_env *env);
static void	end_line_handle(t_exdat *data, t_env *env);
static void	invoke_builtin(t_command *cmd, t_env *env);

int	call_pipe_line(t_command **cmd_lst, t_env *env, t_exdat *data)
{
	while ((*cmd_lst))
	{
		pipe(data->pipefd[((*cmd_lst)->id + 1) % 2]);
		env->child_pid = fork();
		if ((*cmd_lst)->id != 0)
			wait(&(data->status));
		if (env->child_pid == 0)
		{
			pre_handle((*cmd_lst), data, env);
			if ((*cmd_lst)->builtin_flag)
				invoke_builtin((*cmd_lst), env);
			else
				call_execve((*cmd_lst), env);
		}
		if ((*cmd_lst)->redir_in == 2)
			waitpid(env->child_pid, &(data->status), 0);
		if ((*cmd_lst)->redir_in == 1)
			data->rd_in = 1;
		close_parent_pipes((*cmd_lst), data->pipefd);
		(*cmd_lst) = (*cmd_lst)->next;
		if ((*cmd_lst) && (*cmd_lst)->redir_in == 0)
			break ;
	}
	end_line_handle(data, env);
	return (ft_wiexitstatus(data->status));
}

static void	end_line_handle(t_exdat *data, t_env *env)
{
	if (data->rd_in)
		waitpid(env->child_pid, &(data->status), 0);
	else
		wait(&(data->status));
	close_all_pipes(data->pipefd);
}

static void	invoke_builtin(t_command *cmd, t_env *env)
{
	call_builtin(cmd, env);
	exit(env->last_exit_status);
}

static int	pre_handle(t_command *cmd, t_exdat *data, t_env *env)
{
	if (redirect_in_handle(cmd, data, env))
		return (close_child_pipes(cmd, data->pipefd), exit (1), 1);
	if (redirect_out_handle(cmd, data, env))
		return (close_child_pipes(cmd, data->pipefd), exit (1), 1);
	close_child_pipes(cmd, data->pipefd);
	return (0);
}
