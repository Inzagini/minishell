#include "minishell.h"

int	executor(t_command *lst_cmd)
{
	int	pipefd[2];
	pid_t	pid;

	pipe(&pipefd[0]);
	pipe(&pipefd[1]);

	int n = -1;



	return (0);
}

// void	child_processes(t_command data, int **pipe, int file_out_fd)
// {
// 	int		n;
// 	pid_t	pid;

// 	n = -1;
// 	while (++n < data.n_args - 3)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (dup2(pipe[n][0], STDIN_FILENO) == -1)
// 				return ;
// 			if (n != data.n_args - 4)
// 				if (dup2(pipe[n + 1][1], STDOUT_FILENO) == -1)
// 					return ;
// 			if (n == data.n_args - 4)
// 				if (dup2(file_out_fd, STDOUT_FILENO) == -1)
// 					return ;
// 			close_pipes(n, pipe, data.n_args - 3);
// 			call_execve(data, n);
// 		}
// 	}
// }

// void	call_execve(t_command data, int n)
// {
// 	int	status;

// 	if (!data.cmd_lst[n] || !data.cmd_lst[n][0])
// 		print_error(my_getenv("SHELL"), "command not found", NULL);
// 	else
// 	{
// 		status = execve(data.cmd_lst[n][0], data.cmd_lst[n], data.envp);
// 		if (status == -1)
// 		{
// 			print_error(my_getenv("SHELL"),
// 				"command not found", data.cmd_lst[n][0]);
// 			exit(127);
// 		}
// 		else
// 			exit(errno);
// 	}
// }
