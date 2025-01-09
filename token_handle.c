#include "minishell.h"

int	sep_handle(char *str, t_data *data, t_token **head)
{
	t_token	*new_token;

	printf("[SEP]\n");
	new_token = create_token(NULL, SEP);
	if (!new_token)
		return (1);
	append_token_lst(head, new_token);
	while (str[(data->index)] == ' ')
		(data->index)++;
	data->start = data->index;
	return (0);
}

int	arg_handle(char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;
	char	*str;

	if (input_str[data->start] == ' ')
		(data->start)++;
	str = ft_substr(input_str, data->start, data->index + 1 - data->start);
	if (!str)
		return (1);
	new_token = create_token(str, ARG);
	if (!new_token)
		return (free(str), 1);
	append_token_lst(head, new_token);
	data->start = data->index;
	data->rd_flag = 0;
	printf("[ARG]%s\n", str);
	return (0);
}

int	cmd_handle(char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;
	char	*str;

	if (input_str[data->start] == ' ')
		(data->start)++;
	str = ft_substr(input_str, data->start, data->index + 1 - data->start);
	if (!str)
		return (1);
	new_token = create_token(str, CMD);
	if (!new_token)
		return (free(str), 1);
	append_token_lst(head, new_token);
	data->start = data->index;
	data->cmd_flag = 1;
	printf("[CMD]%s\n", str);
	return (0);
}

int	squote_handle(char *str, t_data *data, t_token **head)
{
	t_token	*token;
	int		start;
	char	*sub_str;

	printf("[SQUOTES]\n");
	token = create_token(NULL, SQUOTE);
	append_token_lst(head, token);
	start = ++(data->index);
	while (str[data->index] && str[data->index] != '\'')
		(data->index)++;
	sub_str = ft_substr(str, start, data->index - start);
	token = create_token(sub_str, ARG);
	append_token_lst(head, token);
	printf("[ARG]%s\n", sub_str);
	if (str[data->index] == '\'')
	{
		printf("[SQUOTES]\n");
		token = create_token(NULL, SQUOTE);
		append_token_lst(head, token);
	}
	data->start = data->index;
	return (0);
}

int	dquote_handle(char *str, t_data *data, t_token **head)
{
	t_token	*token;
	int		start;
	char	*sub_str;

	printf("[DQUOTES]\n");
	token = create_token(NULL, DQUOTE);
	append_token_lst(head, token);
	start = ++(data->index);
	while (str[data->index] && str[data->index] != '"')
		(data->index)++;
	sub_str = ft_substr(str, start, data->index - start);
	token = create_token(sub_str, ARG);
	append_token_lst(head, token);
	printf("[ARG]%s\n", sub_str);
	if (str[data->index] == '"')
	{
		printf("[DQUOTES]\n");
		token = create_token(NULL, DQUOTE);
		append_token_lst(head, token);
	}
	data->start = data->index;
	return (0);
}
