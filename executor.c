#include "minishell.h"

void	executor(t_command *cmd_list, t_env *env)
{
	t_exdat	data;

	executor_init(&data);
	while (cmd_list)
	{
		if (cmd_list->builtin_flag && cmd_list->redir_out != 3
			&& cmd_list->redir_in != 3)
		{
			execute_build_in(cmd_list, env);
			cmd_list = cmd_list->next;
		}
		else
		{
			env->last_exit_status = call_pipe_line(&cmd_list, env, &data);
		}
	}
}

void	executor_init(t_exdat *data)
{
	pipe(data->pipefd[0]);
	data->in_fd = 0;
	data->out_fd = 1;
	data->rd_in = 0;
}
