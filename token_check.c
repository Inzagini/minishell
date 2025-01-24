#include "minishell.h"

static int	rd_type(t_token_type type);
char	*ending_pipe_handle();

int	check_tokens(char **input, t_token *token_lst, t_env *env)
{
	t_token	*head;

	head = token_lst;

	int rd_flag = 0;
	int	pipe_flag = 0;
	while (token_lst)
	{
		if (rd_type(token_lst->type))
			rd_flag = 1;
		else if (token_lst->type == ARG)
			rd_flag = 0;
		else if (token_lst->type == PIPE)
			pipe_flag = 1;
		else if (token_lst->type == CMD)
			pipe_flag = 0;
		token_lst = token_lst->next;
	}
	if (rd_flag)
	{
		print_err(ft_get("SHELL", env->env),
			"syntax error near unexpected token" , "newline");
		env->last_exit_status = 2;
		return (2);
	}
	else if (pipe_flag)
	{
		char *new_input = ending_pipe_handle();
		token_lst = head;
		*input = new_input;
		return (1);
	}

	token_lst = head;
	return (0);
}

static int	rd_type(t_token_type type)
{
	return (type == RD_IN || type == RD_OUT
		|| type == RD_APP || type == RD_HEREDOC);
}

char	*ending_pipe_handle()
{
	char	buffer[BUFFER_SIZE + 1];
	char	*line;
	char	*tmp;
	ssize_t	bytes_read;

	bytes_read = 1;
	line = ft_strdup("");
	while (bytes_read)
	{
		write(1, "> ", 2);
		bytes_read = read(0, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			break ;
		buffer[bytes_read] = 0;
		tmp = line;
		line = ft_strjoin(line, buffer);
		free(tmp);
		if (ft_strchr((const char *) buffer, '\n'))
			break;
	}
	return (line);
}

