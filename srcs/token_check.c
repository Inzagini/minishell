/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quannguy <quannguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:46:23 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 14:49:57 by quannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	rd_type(t_token_type type);
static char	*ending_pipe_handle(void);
static int	flag_count(t_token *token_lst, t_data *data);

int	check_tokens(char **input, t_token *token_lst, t_env *env)
{
	t_data	flags;
	char	*new_input;
	char	*tmp;

	flag_count(token_lst, &flags);
	if (flags.rd_flag || flags.pipe_flag > 1)
	{
		print_err(ft_get("SHELL", env->env),
			"syntax error near unexpected token", NULL);
		env->last_exit_status = 2;
		return (2);
	}
	else if (flags.pipe_flag)
	{
		tmp = *input;
		new_input = ending_pipe_handle();
		*input = new_input;
		free(tmp);
		return (1);
	}
	return (0);
}

static int	flag_count(t_token *token_lst, t_data *data)
{
	t_token	*head;

	data->rd_flag = 0;
	data->pipe_flag = 0;
	head = token_lst;
	if (token_lst->type == PIPE)
		return (data->rd_flag = 1, 1);
	while (token_lst)
	{
		if (rd_type(token_lst->type))
			data->rd_flag = 1;
		else if (token_lst->type == ARG)
		{
			data->rd_flag = 0;
			data->pipe_flag = 0;
		}
		else if (token_lst->type == PIPE)
			data->pipe_flag++;
		else if (token_lst->type == CMD || token_lst->type == ARG)
			data->pipe_flag = 0;
		token_lst = token_lst->next;
	}
	token_lst = head;
	return (0);
}

static int	rd_type(t_token_type type)
{
	return (type == RD_IN || type == RD_OUT
		|| type == RD_APP || type == RD_HEREDOC);
}

char	*ending_pipe_handle(void)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*line;
	char	*tmp;
	ssize_t	bytes_read;

	bytes_read = 1;
	line = ft_strdup(" ");
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
			break ;
	}
	line[ft_strlen(line) - 1] = 0;
	return (line);
}
