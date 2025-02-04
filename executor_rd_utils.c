#include "minishell.h"

int	open_infile_handle(t_command *cmd_node, t_exdat *data, t_env *env);
int	open_outfile_handle(t_command *cmd_node, t_exdat *data, t_env *env);
int	here_doc_handle(t_command *cmd_node, t_env *env);

int	redirect_in_handle(t_command *cmd_node, t_exdat *data, t_env *env)
{
	if (cmd_node->redir_in == 1 || cmd_node->redir_in == 2)
	{
		if (open_infile_handle(cmd_node, data, env))
			return (1);
	}
	else if (cmd_node->redir_in == 3)
	{
		data->in_fd = data->pipefd[1 - (cmd_node->id + 1) % 2][0];
	}
	else if (cmd_node->redir_in == 0)
	{
		data->in_fd = STDIN_FILENO;
	}
	else
		return (1);
	if (dup2(data->in_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 in");
		return (1);
	}
	return (0);
}

int	redirect_out_handle(t_command *cmd_node, t_exdat *data, t_env *env)
{
	if (cmd_node->redir_out == 1 || cmd_node->redir_out == 2)
	{
		if (open_outfile_handle(cmd_node, data, env))
			return (1);
	}
	else if (cmd_node->redir_out == 3)
	{
		data->out_fd = data->pipefd[(cmd_node->id + 1) % 2][1];
	}
	else if (cmd_node->redir_out == 0)
	{
		data->out_fd = STDOUT_FILENO;
	}
	if (dup2(data->out_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 out");
		return (1);
	}
	return (0);
}

int	open_infile_handle(t_command *cmd_node, t_exdat *data, t_env *env)
{
	if (cmd_node->redir_in == 1)
	{
		if (access(cmd_node->redir_file_in, F_OK) == -1
			|| access(cmd_node->redir_file_in, R_OK) == -1)
		{
			print_err(ft_get("SHELL", env->env),
				strerror(errno), cmd_node->redir_file_in);
			return (1);
		}
		else
		{
			data->in_fd = open(cmd_node->redir_file_in, O_RDONLY);
			if (data->in_fd < 0)
				return (perror("Open infile:"), 1);
		}
	}
	else if (cmd_node->redir_in == 2)
	{
		data->in_fd = here_doc_handle(cmd_node, env);
		if (data->in_fd == -1)
			return (1);
	}
	return (0);
}

int	open_outfile_handle(t_command *cmd_node, t_exdat *data, t_env *env)
{
	if (access(cmd_node->redir_file_out, W_OK) != -1)
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
	{
		print_err(ft_get("SHELL", env->env),
			strerror(errno), cmd_node->redir_file_out);
		return (env->last_exit_status = 1, 1);
	}
	return (0);
}
