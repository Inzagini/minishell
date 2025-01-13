#include "minishell.h"

int	meta_char(char *str, t_data *data, t_token **head);
static void	token_init(t_data *data);

int	tokenizer(char *input_str, t_token **head)
{
	t_data	data;

	token_init(&data);
	while (input_str[++(data.index)])
	{
		if (!meta_char(input_str, &data, head))
			continue ;
		else if (input_str[data.index + 1] == ' '
			|| input_str[data.index + 1] == 0
			|| input_str[data.index + 1] == '\n'
			|| input_str[data.index + 1] == '\''
			|| input_str[data.index + 1] == '"')
		{
			if (data.cmd_flag == 0 && !data.rd_flag)
				cmd_handle(input_str, &data, head);
			else
				arg_handle(input_str, &data, head);
		}
		if (data.exit_flag)
			return (1);
	}
	return (0);
}

static void	token_init(t_data *data)
{
	data->index = -1;
	data->start = 0;
	data->cmd_flag = 0;
	data->rd_flag = 0;
	data->exit_flag = 0;
}

int	meta_char(char *input_str, t_data *data, t_token **head)
{
	if (input_str[data->index] == ' ')
		sep_handle(input_str, data, head);
	if (input_str[data->index] == '|')
		pipe_handle(input_str, data, head);
	else if (input_str[data->index] == '\'')
		squote_handle(input_str, data, head);
	else if (input_str[data->index] == '"')
		dquote_handle(input_str, data, head);
	else if (input_str[data->index] == '\n')
		new_line_handle(data, head);
	else if (input_str[data->index] == '>'
		|| input_str[data->index] == '<')
		rd_handle(input_str, data, head);
	else
		return (1);
	return (0);
}

t_token	*create_token(char *content, t_token_type token_type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = token_type;
	new_token->content = content;
	new_token->previous = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	append_token_lst(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
	new_token->previous = tmp;
}
