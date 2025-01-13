#include "minishell.h"

int	redirect_in_handle(t_command *cmd_node, int **pipefd);
int	redirect_out_handle(t_command *cmd_node, int **pipefd);
void	call_execve(t_command *data);

int	executor(t_command *lst_cmd)
{
	int	*pipefd[2];
	pid_t	pid;

	pipe(pipefd[0]);
	pipe(pipefd[1]);
	int n = -1;
	int	len = lst_len(lst_cmd);

	while (++n < len)
	{
		if (n != 0)
		{
			// printf("OPEN NEW PIPE for STDOUT %d\n", (lst_cmd->id + 1) % 2);
			pipe(pipefd[(lst_cmd->id + 1) % 2]);
		}
		pid = fork();
		if (pid == 0)
		{
			// redirect STDIN to appropiate fd
			int	IN_FD = redirect_in_handle(lst_cmd, pipefd);
			if (dup2(IN_FD, STDIN_FILENO) == -1)
			{
				perror("redirect 1\n");
				return (1);
			}
			//redire STDOUT to appropiate fd
			int	OUT_FD = redirect_out_handle(lst_cmd, pipefd);
			if (dup2(OUT_FD, STDOUT_FILENO) == -1)
			{
				perror("redirect 2\n");
				return (1);
			}

			//close the pipe
			// printf("child close IN PIPE %d\n", 1 - ((lst_cmd->id + 1) % 2));
			if (lst_cmd->redir_in)
				close(IN_FD);
			close(pipefd[1 - ((lst_cmd->id + 1) % 2)][0]);
			close(pipefd[((lst_cmd->id + 1) % 2)][1]);
			close(pipefd[((lst_cmd->id + 1) % 2)][0]);
			// printf("\nexecute\n");
			// printf("\n\n----------------\n");
			call_execve(lst_cmd);
		}
		// printf("Parent close pipe %d \n", 1 - (lst_cmd->id + 1) % 2);
		close (pipefd[1 - (lst_cmd->id + 1) % 2][0]);
		close (pipefd[1 - (lst_cmd->id + 1) % 2][1]);
		close (pipefd[(lst_cmd->id + 1) % 2][1]);
		// printf("------------\n\n");
		lst_cmd = lst_cmd->next;
	}

	wait(NULL);
	close (pipefd[0][0]);
	close (pipefd[0][1]);
	close (pipefd[1][0]);
	close (pipefd[1][1]);
	return (0);
}

void	call_execve(t_command *data)
{
	int	status;

	if (!data->arguments || !data->arguments[0])
		print_error(getenv("SHELL"), "command not found", NULL);
	else
	{
		status = execve(data->arguments[0], data->arguments, NULL);
		if (status == -1)
		{
			print_error(getenv("SHELL"),
				"command not found", data->arguments[0]);
			exit(127);
		}
		else
			exit(errno);
	}
}

int	redirect_in_handle(t_command *cmd_node, int **pipefd)
{
	int	fd;

	if (cmd_node->redir_in == 1)
	{
		// printf("read from %s\n", cmd_node->redir_file_in);
		//check if file exist
		fd = open(cmd_node->redir_file_in, O_RDONLY);
		if (fd < 0)
		{
			perror("Error redir IN\n");
			exit(1);
		}
		//check return of open
		return (fd);
	}
	else if (cmd_node->redir_in == 2)
	{
		//here doc
		printf("Not supported\n");
		return (2);
	}
	else if (cmd_node->redir_in == 3)
	{
		// printf("redirect STDIN to pipes %d\n", 1 - ((cmd_node->id + 1) % 2));
		fd = pipefd[1 - ((cmd_node->id + 1) % 2)][0];
		return (fd);
	}
	else
	{
		// printf("read STDIN\n");
		return (STDIN_FILENO);
	}
}

int	redirect_out_handle(t_command *cmd_node, int **pipefd)
{
	int	fd;

	if (cmd_node->redir_out == 1 || cmd_node->redir_out == 2)
	{
		if (access(cmd_node->redir_file_out, F_OK) == -1)
		{
			printf("create file\n");
			fd = open(cmd_node->redir_file_out, O_WRONLY | O_CREAT, 0666);
		}
		else if (access(cmd_node->redir_file_out, W_OK) != -1)
		{
			if (cmd_node->redir_out == 1)
			{
				// ft_putstr_fd("open truncate\n", 1);
				fd = open(cmd_node->redir_file_out, O_WRONLY | O_TRUNC);
				if (fd < 0)
					perror("Error write\n");
			}
			else if (cmd_node->redir_out == 2)
			{
				// ft_putstr_fd("open append\n", 1);
				fd = open(cmd_node->redir_file_out, O_WRONLY | O_APPEND);
				if (fd < 0)
					perror("Error append\n");
			}
		}
		else
			perror("Error redir out\n");
		return (fd);
	}
	else if (cmd_node->redir_out == 3)
	{
		//pipe
		// printf("redirect STDOUT to pipes %d\n", (cmd_node->id + 1) % 2);
		fd = pipefd[(cmd_node->id + 1) % 2][1];
		return (fd);
	}
	else
	{
		// printf("write STDOUT\n");
		return (STDOUT_FILENO);
	}
}
