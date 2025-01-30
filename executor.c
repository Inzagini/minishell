#include "minishell.h"

void	executor(t_command *cmd_list, t_env *env)
{
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
			call_pipe_line(&cmd_list, env);
			env->last_exit_status = exit_check(env);
		}
	}
}

