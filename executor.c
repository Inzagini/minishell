#include "minishell.h"

void	executor(t_command *cmd_list, t_env *env)
{
	int	len;

	len = lst_len(cmd_list);
	if (cmd_list->builtin_flag && lst_len(cmd_list) < 2) // we need to call commands that are not part of a "|""
		call_builtin(cmd_list, env);
	else
	{
		call_pipe_line(cmd_list, env);
		env->last_exit_status = exit_check(len);
	}
}
