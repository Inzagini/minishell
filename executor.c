#include "minishell.h"

int	redirect_in_handle(t_command *cmd_node, int *pipefd);
int	redirect_out_handle(t_command *cmd_node, int *pipefd);

int	executor(t_command *lst_cmd)
{
	int	pipefd[2];
	pid_t	pid;

	// pipe(&pipefd[0]);
	// pipe(&pipefd[1]);
	printf("Initial pipe open\n");
	int n = -1;
	int	len = lst_len(lst_cmd);
	printf("lst len %d\n", len);
	//loop through all command node
	while (++n < len)
	{
		//open appropiate pipe
		if (n != 0)
			printf("OPEN NEW STDOUT %d\n", (lst_cmd->id + 1) % 2);
		//fork the process
		pid = fork();
		//child process
		if (pid == 0)
		{
			//redirect STDIN to appropiate fd
			redirect_in_handle(lst_cmd, pipefd);
			//redire STDOUT to appropiate fd
			redirect_out_handle(lst_cmd, pipefd);

			//close the pipe
			printf("close IN PIPE %d\n", 1 - ((lst_cmd->id + 1) % 2));
			//execute command
			printf("execute command\n");
		}

		printf("------------\n\n");
		wait(NULL);
		lst_cmd = lst_cmd->next;
	}


	return (0);
}

// void	call_execve(t_command data, int n)
// {
// 	int	status;

// 	if (!data.arguments || !data.arguments[n][0])
// 		print_error(my_getenv("SHELL"), "command not found", NULL);
// 	else
// 	{
// 		status = execve(data.arguments[n][0], data.arguments[n], NULL);
// 		if (status == -1)
// 		{
// 			print_error(my_getenv("SHELL"),
// 				"command not found", data.arguments[n][0]);
// 			exit(127);
// 		}
// 		else
// 			exit(errno);
// 	}
// }

int	redirect_in_handle(t_command *cmd_node, int *pipefd)
{
	if (cmd_node->redir_in == 1)
	{
		//open file
		printf("open read\n");
		return (1);
	}
	else if (cmd_node->redir_in == 2)
	{
		//here doc
		printf("Not supported\n");
		return (2);
	}
	else if (cmd_node->redir_in == 3)
	{
		//pipe
		printf("redirect STDIN to pipes %d\n", 1 - ((cmd_node->id + 1) % 2));
		return (3);
	}
	else
		return (STDIN_FILENO);
}

int	redirect_out_handle(t_command *cmd_node, int *pipefd)
{
	if (cmd_node->redir_out == 1)
	{
		//open file
		printf("open truncate\n");
		return (1);
	}
	else if (cmd_node->redir_out == 2)
	{
		//append to file
		printf("append to file\n");
		return (2);
	}
	else if (cmd_node->redir_out == 3)
	{
		//pipe
		printf("redirect STDOUT to pipes %d\n", (cmd_node->id + 1) % 2);
		return (3);
	}
	else
		return (STDOUT_FILENO);
}
