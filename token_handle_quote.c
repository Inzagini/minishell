#include "minishell.h"

int	new_line_handle (char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;

	new_token = create_token(NULL, NEW_LINE);
	if (!new_token)
		return (1);
	append_token_lst(head, new_token);
	data->cmd_flag = 0;
	(data->index)++;
	data->start = data->index;
	printf("[NEW_LINE]\n");
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
