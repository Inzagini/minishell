#include "minishell.h"

int	cmd_handle(char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;
	char	*str;

	if (input_str[data->start] == ' ')
		(data->start)++;
	str = ft_substr((const char *)input_str, data->start,
			data->index + 1 - data->start);
	if (!str)
		return (data->exit_flag = 1, 1);
	new_token = create_token(str, CMD);
	if (!new_token)
	{
		free(str);
		return (data->exit_flag = 1, 1);
	}
	append_token_lst(head, new_token);
	data->start = data->index;
	data->cmd_flag = 1;
	// if (input_str[data->index + 1] == 0)
	// 	data->exit_flag = 1;
	// printf("[CMD]%s\n", str);
	return (0);
}

int	arg_handle(char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;
	char	*str;

	if (input_str[data->start] == ' ')
		(data->start)++;
	if (!input_str[data->start])
		return (0);
	str = ft_substr((const char *)input_str, data->start,
			data->index + 1 - data->start);
	if (!str)
		return (data->exit_flag = 1, 1);
	new_token = create_token(str, ARG);
	if (!new_token)
	{
		free(str);
		return (data->exit_flag = 1, 1);
	}
	append_token_lst(head, new_token);
	data->start = data->index;
	data->rd_flag = 0;
	// if (input_str[data->index + 1] == 0)
	// 	data->exit_flag = 1;
	// printf("[ARG]%s\n", str);
	return (0);
}

int	sep_handle(char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;

	new_token = create_token(NULL, SEP);
	if (!new_token)
		return (data->exit_flag = 1, 1);
	append_token_lst(head, new_token);
	while (input_str[(data->index)] == ' ')
		(data->index)++;
	data->start = data->index;
	// if (!input_str[data->index])
	// 	data->exit_flag = 1;
	// printf("[SEP]\n");
	return (0);
}

int	pipe_handle(char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;

	if (input_str[data->index + 1] != ' ')
		data->index++;
	new_token = create_token(NULL, PIPE);
	if (!new_token)
		return (data->exit_flag = 1, 1);
	append_token_lst(head, new_token);
	data->start = data->index;
	data->cmd_flag = 0;
	// printf("[PIPE]\n");
	return (0);
}
