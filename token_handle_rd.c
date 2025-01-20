#include "minishell.h"

int	rd_handle(char *input_str, t_data *data, t_token **head)
{
	if (input_str[data->index] == '>')
	{
		if (input_str[data->index + 1] == '>')
			rd_app_handle(input_str, data, head);
		else
			rd_out_handle(input_str, data, head);
	}
	else if (input_str[data->index] == '<')
	{
		if (input_str[data->index + 1] == '<')
			rd_heredoc_handle(input_str, data, head);
		else
			rd_in_handle(input_str, data, head);
	}
	return (0);
}

int	rd_out_handle(char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;

	if (input_str[data->index + 1] != ' ')
		data->index++;
	new_token = create_token(NULL, RD_OUT);
	if (!new_token)
		return (data->exit_flag = 1, 1);
	append_token_lst(head, new_token);
	data->start = data->index;
	data->rd_flag = 1;
	data->exit_flag = 0;
	return (0);
}

int	rd_in_handle(char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;

	if (input_str[data->index + 1] != ' ')
		data->index++;
	new_token = create_token(NULL, RD_IN);
	if (!new_token)
		return (data->exit_flag = 1, 1);
	append_token_lst(head, new_token);
	data->start = data->index;
	data->rd_flag = 1;
	data->exit_flag = 0;
	return (0);
}

int	rd_app_handle(char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;

	if (input_str[data->index + 2] != ' ')
		data->index += 2;
	else
		data->index += 1;
	new_token = create_token(NULL, RD_APP);
	if (!new_token)
		return (data->exit_flag = 1, 1);
	append_token_lst(head, new_token);
	data->start = data->index;
	data->rd_flag = 1;
	return (0);
}

int	rd_heredoc_handle(char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;

	if (input_str[data->index + 2] != ' ')
		data->index += 2;
	else
		data->index += 1;
	new_token = create_token(NULL, RD_HEREDOC);
	if (!new_token)
		return (data->exit_flag = 1, 1);
	append_token_lst(head, new_token);
	data->start = data->index;
	data->rd_flag = 1;
	return (0);
}
