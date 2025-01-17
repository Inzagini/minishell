#include "minishell.h"

int	is_pipes(t_command *cmd_list);

void	executor(t_command *cmd_list, t_env *env)
{
	int	len;

	len = lst_len(cmd_list);
	while (cmd_list)
	{
		if (cmd_list->builtin_flag && cmd_list->redir_out != 3 &&
			cmd_list->redir_in != 3)
		{
			execute_build_in(cmd_list, env);
			cmd_list = cmd_list->next;
		}
		else
		{
			call_pipe_line(&cmd_list, env);
			env->last_exit_status = exit_check(len);
		}
	}
}

int	is_pipes(t_command *cmd_list)
{
	t_command *head;

	head = cmd_list;
	while (cmd_list)
	{
		if (cmd_list->redir_out == 3)
		{
			cmd_list = head;
			return (1);
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}
