#include "minishell.h"

int	call_pipe_line(t_command **cmd_lst, t_env *env)
{
	t_exdat	data;

	executor_init(&data);
	while ((*cmd_lst))
	{
		if ((*cmd_lst)->id != 0)
			pipe(data.pipefd[((*cmd_lst)->id + 1) % 2]);
		env->child_pid = fork();
		if (env->child_pid == 0)
		{
			pre_handle((*cmd_lst), &data);
			if ((*cmd_lst)->builtin_flag)
				invoke_builtin((*cmd_lst), env);
			else
				call_execve((*cmd_lst), env);
			close_child_pipes(*cmd_lst, data.pipefd);
		}
		waitpid(env->child_pid, NULL, 0);
		close_parent_pipes((*cmd_lst), data.pipefd);
		(*cmd_lst) = (*cmd_lst)->next;
		if ((*cmd_lst))
			if ((*cmd_lst)->redir_in == 0)
				break ;
	}
	close_all_pipes(data.pipefd);
	return (0);
}

void	invoke_builtin(t_command *cmd, t_env *env)
{
	call_builtin(cmd, env);
	exit(env->last_exit_status);
}

void	call_execve(t_command *data, t_env *env)
{
	int	status;

	if (!data->args || !data->args[0])
		print_err(ft_get("SHELL", env->env),
			"command not found", NULL);
	else
	{
		status = execve(data->args[0], data->args, env->env);
		if (status == -1)
		{
			print_err(ft_get("SHELL", env->env),
				"command not found", data->args[0]);
			exit(127);
		}
		else
			exit(errno);
	}
}

void	executor_init(t_exdat *data)
{
	pipe(data->pipefd[0]);
	pipe(data->pipefd[1]);
	data->in_fd = 0;
	data->out_fd = 1;
}

void	pre_handle(t_command *cmd, t_exdat *data)
{
	redirect_in_handle(cmd, data);
	redirect_out_handle(cmd, data);
	close_child_pipes(cmd, data->pipefd);
}
