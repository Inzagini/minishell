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
			exit(1);
		}
		else
		{
			data->in_fd = open(cmd_node->redir_file_in, O_RDONLY);
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

int	here_doc_handle(t_command *cmd_node, t_env *env)
{
	char	*delimiter;
	char	buffer[BUFFER_SIZE + 1];
	int		pipefd[2];
	char	*expanded;
	ssize_t	bytes_read;
	struct sigaction	sa_old;
	struct sigaction	sa_new;

	bytes_read = 1;
	delimiter = cmd_node->heredoc_separator;
	pipe(pipefd);

	sa_new.sa_handler = heredoc_signal_handler;
	sa_new.sa_flags = 0;
	sigemptyset(&sa_new.sa_mask);
	sigaction(SIGINT, &sa_new, &sa_old);

	while (bytes_read)
	{
		write(1, "> ", 2);
		bytes_read = read(0, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			break ;
		if (bytes_read == 0)
		{
			write(2, "\n", 1);
			print_err(ft_get("SHELL", env->env), "here-document at line 16 delimited by end-of-file", NULL);
			break ;
		}
		buffer[bytes_read] = 0;
		if (ft_strncmp(buffer, delimiter, ft_strlen(delimiter) + 1) == 10)
			break ;
		if (ft_strchr(buffer, '$'))
		{
			expanded = expand_argument(buffer, env->env, expanded);
			write(pipefd[1], expanded, ft_strlen(expanded));
			free (expanded);
		}
		else
			write(pipefd[1], buffer, bytes_read);
	}
	close(pipefd[1]);
	sigaction(SIGINT, &sa_old, NULL);
	if (g_heredoc_interrupted)
	{
		close(pipefd[0]);
		exit(130);
	}
	return (pipefd[0]);
}
