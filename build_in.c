#include "minishell.h"

static int	pre_handle(t_command *cmd, t_exdat *data, t_env *env);
static void	reset_fds(int origin_in, int origin_out);

void	execute_build_in(t_command *cmd, t_env *env)
{
	t_exdat	data;
	int		origin_in;
	int		origin_out;

	origin_in = dup(STDIN_FILENO);
	origin_out = dup(STDOUT_FILENO);
	executor_init(&data);
	if (pre_handle(cmd, &data, env))
	{
		env->last_exit_status = 1;
		reset_fds(origin_in, origin_out);
		return ;
	}
	call_builtin(cmd, env);
	close(data.pipefd[1 - ((cmd->id + 1) % 2)][1]);
	reset_fds(origin_in, origin_out);
}

void	call_builtin(t_command *cmd, t_env *env)
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
		ft_exit(cmd, env);
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
		dup2(origin_in, STDIN_FILENO);
		close(origin_in);
	}
	if (origin_out != -1)
	{
		dup2(origin_out, STDOUT_FILENO);
		close(origin_out);
	}
}
