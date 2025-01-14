#include "minishell.h"

void	call_execve(t_command *data);
void	executor_init(t_exdat *data);

int	executor(t_command *lst_cmd)
{
	t_exdat	data;

	executor_init(&data);
	while (lst_cmd)
	{
		if (lst_cmd->id != 0)
			pipe(data.pipefd[(lst_cmd->id + 1) % 2]);
		data.pid = fork();
		if (data.pid == 0)
		{
			redirect_in_handle(lst_cmd, &data);
			redirect_out_handle(lst_cmd, &data);
			close_child_pipes(lst_cmd, data.pipefd);
			call_execve(lst_cmd);
		}
		close_parent_pipes(lst_cmd, data.pipefd);
		lst_cmd = lst_cmd->next;
	}
	wait(NULL);
	close_all_pipes(data.pipefd);
	return (0);
}

void	call_execve(t_command *data)
{
	int	status;

	if (!data->args || !data->args[0])
		print_error(getenv("SHELL"), "command not found", NULL);
	else
	{
		status = execve(data->args[0], data->args, NULL);
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

void	executor_init(t_exdat *data)
{
	pipe(data->pipefd[0]);
	pipe(data->pipefd[1]);
	data->in_fd = 0;
	data->out_fd = 1;
}
