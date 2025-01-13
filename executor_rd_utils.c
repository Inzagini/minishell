#include "minishell.h"

int	redirect_in_handle(t_command *cmd_node, int pipefd[2][2])
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

int	redirect_out_handle(t_command *cmd_node, int pipefd[2][2])
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
