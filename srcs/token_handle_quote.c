/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:46:52 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:46:53 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quotes_helper(char *input_str, t_data *data, t_token **head);

int	new_line_handle(char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;

	new_token = create_token(NULL, NEW_LINE);
	if (!new_token)
		return (data->exit_flag = 1, 1);
	append_token_lst(head, new_token);
	data->cmd_flag = 0;
	if (input_str[data->index + 1] == ' ')
		(data->index)++;
	data->start = data->index + 1;
	return (0);
}

int	squote_handle(char *input_str, t_data *data, t_token **head)
{
	if (token_quotes(head, data, SQUOTE))
		return (data->exit_flag = 1, 1);
	data->start = ++(data->index);
	while (input_str[data->index] && input_str[data->index] != '\'')
		(data->index)++;
	if (!input_str[data->index])
	{
		print_err(NULL, "Error: unclosed quote", NULL);
		return (data->exit_flag = 1, 1);
	}
	if (quotes_helper(input_str, data, head))
		return (data->exit_flag = 1, 1);
	if (input_str[data->index] == '\'')
	{
		if (token_quotes(head, data, SQUOTE))
			return (data->exit_flag = 1, 1);
		data->start = data->index + 1;
		return (0);
	}
	data->start = data->index;
	return (0);
}

int	dquote_handle(char *input_str, t_data *data, t_token **head)
{
	if (token_quotes(head, data, DQUOTE))
		return (data->exit_flag = 1, 1);
	data->start = ++(data->index);
	while (input_str[data->index] && input_str[data->index] != '"')
		(data->index)++;
	if (!input_str[data->index])
	{
		print_err(NULL, "Error: unclosed quote", NULL);
		return (data->exit_flag = 1, 1);
	}
	if (quotes_helper(input_str, data, head))
		return (data->exit_flag = 1, 1);
	if (input_str[data->index] == '"')
	{
		if (token_quotes(head, data, DQUOTE))
			return (data->exit_flag = 1, 1);
		data->start = data->index + 1;
		return (0);
	}
	data->start = data->index;
	return (0);
}

static int	quotes_helper(char *input_str, t_data *data, t_token **head)
{
	t_token	*new_token;
	char	*str;

	if (input_str[data->index] == 0)
		return (1);
	str = ft_substr(input_str, data->start, data->index - data->start);
	if (!str)
		return (1);
	new_token = create_token(str, ARG);
	if (!new_token)
		return (1);
	append_token_lst(head, new_token);
	return (0);
}
