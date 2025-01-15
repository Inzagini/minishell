#include "minishell.h"

static void	call_execve(t_command *data, t_env *env);
static void	executor_init(t_exdat *data);

int	executor(t_command *cmd_lst, t_env *env)
{
	t_exdat	data;

	executor_init(&data);
	while (cmd_lst)
	{
		if (cmd_lst->id != 0)
			pipe(data.pipefd[(cmd_lst->id + 1) % 2]);
		data.pid = fork();
		if (data.pid == 0)
		{
			redirect_in_handle(cmd_lst, &data);
			redirect_out_handle(cmd_lst, &data);
			close_child_pipes(cmd_lst, data.pipefd);
			if (cmd_lst->builtin_flag)
				call_build_in(cmd_lst, env);
			else
				call_execve(cmd_lst, env);
		}
		close_parent_pipes(cmd_lst, data.pipefd);
		cmd_lst = cmd_lst->next;
	}
	wait(NULL);
	close_all_pipes(data.pipefd);
	return (0);
}

static void	call_execve(t_command *data, t_env *env)
{
	int	status;

	if (!data->args || !data->args[0])
		print_error(getenv("SHELL"), "command not found", NULL);
	else
	{
		status = execve(data->args[0], data->args, env->env_current);
		if (status == -1)
		{
			print_error(getenv("SHELL"),
				"command not found", data->args[0]);
			exit(127);
		}
		else
			exit(errno);
	}
}

static void	executor_init(t_exdat *data)
{
	pipe(data->pipefd[0]);
	pipe(data->pipefd[1]);
	data->in_fd = 0;
	data->out_fd = 1;
}
