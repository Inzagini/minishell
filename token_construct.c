#include "minishell.h"

static int	meta_char(char *str, t_data *data, t_token **head);
static void	token_init(t_data *data);
static int	is_symbol_char(char c);

int	token_construct(char *input_str, t_token **head)
{
	t_data	data;

	token_init(&data);
	while (input_str[++(data.index)] != '\0')
	{
		if (!meta_char(input_str, &data, head))
		{
		}
		else if (is_symbol_char(input_str[data.index + 1])
			&& !data.exit_flag)
		{
			if (data.cmd_flag == 0 && !data.rd_flag)
				cmd_handle(input_str, &data, head);
			else
				arg_handle(input_str, &data, head);
		}
		if (data.exit_flag)
			return (1);
	}
	free(input_str);
	input_str = NULL;
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
		if(sep_handle(input_str, data, head))
			return (0);
	if (input_str[data->index] == '|')
		pipe_handle(data, head);
	else if (input_str[data->index] == '\'')
		squote_handle(input_str, data, head);
	else if (input_str[data->index] == '"')
		dquote_handle(input_str, data, head);
	else if (input_str[data->index] == '\n')
		new_line_handle(input_str, data, head);
	else if (input_str[data->index] == '>'
		|| input_str[data->index] == '<')
		rd_handle(input_str, data, head);
	else
		return (1);
	return (0);
}

int	is_symbol_char(char c)
{
	return (c == ' ' || c == '\0' || c == '\n'
		|| c == '\'' || c == '"' || c == '|'
		|| c == '>' || c == '<');
}
