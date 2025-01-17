#include "minishell.h"

int	open_infile_handle(t_command *cmd_node, t_exdat *data);
int	open_outfile_handle(t_command *cmd_node, t_exdat *data);

int	redirect_in_handle(t_command *cmd_node, t_exdat *data)
{
	if (cmd_node->redir_in == 1 || cmd_node->redir_in == 2) // add herefile support
	{
		open_infile_handle(cmd_node, data);
	}
	else if (cmd_node->redir_in == 3)
	{
		data->in_fd = data->pipefd[1 - ((cmd_node->id + 1) % 2)][0];
	}
	else if (cmd_node->redir_in == 0)
	{
		data->in_fd = STDIN_FILENO;
	}
	else
		return (1);
	if (dup2(data->in_fd, STDIN_FILENO) == -1)
		return (1);
	return (0);
}

int	redirect_out_handle(t_command *cmd_node, t_exdat *data)
{
	if (cmd_node->redir_out == 1 || cmd_node->redir_out == 2)
	{
		open_outfile_handle(cmd_node, data);
	}
	else if (cmd_node->redir_out == 3)
	{
		data->out_fd = data->pipefd[(cmd_node->id + 1) % 2][1];
	}
	else if (cmd_node->redir_out == 0)
		data->out_fd = STDOUT_FILENO;
	else
		return (1);
	if (dup2(data->out_fd, STDOUT_FILENO) == -1)
		return (1);
	return (0);
}

int	open_infile_handle(t_command *cmd_node, t_exdat *data)
{
	if (access(cmd_node->redir_file_in, F_OK) == -1
		|| access(cmd_node->redir_file_in, R_OK) == -1)
	{
		print_error(getenv("SHELL"), strerror(errno), cmd_node->redir_file_in);
	}
	else
	{
		data->in_fd = open(cmd_node->redir_file_in, O_RDONLY);
	}
	return (0);
}

int	open_outfile_handle(t_command *cmd_node, t_exdat *data)
{
	if (access(cmd_node->redir_file_out, F_OK) == -1)
	{
		data->out_fd = open(cmd_node->redir_file_out, O_WRONLY | O_CREAT, 0666);
	}
	else if (access(cmd_node->redir_file_out, W_OK) != -1)
	{
		if (cmd_node->redir_out == 1)
		{
			data->out_fd = open(cmd_node->redir_file_out, O_WRONLY | O_TRUNC);
			if (data->out_fd < 0)
				perror("Error write\n");
		}
		else if (cmd_node->redir_out == 2)
		{
			data->out_fd = open(cmd_node->redir_file_out, O_WRONLY | O_APPEND);
			if (data->out_fd < 0)
				perror("Error append\n");
		}
	}
	else
		perror("Error redir out\n");
	return (0);
}
