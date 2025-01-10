#include "minishell.h"

int	quotes_helper(char *input_str, t_data *data, t_token **head);

int	new_line_handle(t_data *data, t_token **head)
{
	t_token	*new_token;

	new_token = create_token(NULL, NEW_LINE);
	if (!new_token)
		return (data->exit_flag = 1, 1);
	append_token_lst(head, new_token);
	data->cmd_flag = 0;
	(data->index)++;
	data->start = data->index;
	printf("[NEW_LINE]\n");
	return (0);
}

int	squote_handle(char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;

	printf("[SQUOTES]\n");
	new_token = create_token(NULL, SQUOTE);
	if (!new_token)
		return (data->exit_flag = 1, 1);
	append_token_lst(head, new_token);
	data->start = ++(data->index);
	while (input_str[data->index] && input_str[data->index] != '\'')
		(data->index)++;
	if (quotes_helper(input_str, data, head))
		return (data->exit_flag = 1, 1);
	if (input_str[data->index] == '\'')
	{
		printf("[SQUOTES]\n");
		new_token = create_token(NULL, SQUOTE);
		if (!new_token)
			return (data->exit_flag = 1, 1);
		append_token_lst(head, new_token);
	}
	data->start = data->index;
	return (0);
}

int	dquote_handle(char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;

	printf("[DQUOTES]\n");
	new_token = create_token(NULL, DQUOTE);
	if (!new_token)
		return (data->exit_flag = 1, 1);
	append_token_lst(head, new_token);
	data->start = ++(data->index);
	while (input_str[data->index] && input_str[data->index] != '"')
		(data->index)++;
	if (quotes_helper(input_str, data, head))
		return (data->exit_flag = 1, 1);
	if (input_str[data->index] == '"')
	{
		printf("[DQUOTES]\n");
		new_token = create_token(NULL, DQUOTE);
		if (!new_token)
			return (data->exit_flag = 1, 1);
		append_token_lst(head, new_token);
	}
	data->start = data->index;
	return (0);
}

int	quotes_helper(char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;
	char	*str;

	str = ft_substr(input_str, data->start, data->index - data->start);
	if (!str)
		return (1);
	new_token = create_token(str, ARG);
	if (!new_token)
		return (1);
	append_token_lst(head, new_token);
	printf("[ARG]%s\n", str);
	return (0);
}
