/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:47:09 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:47:10 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!input_str[data->index])
		return (1);
	return (0);
}

int	pipe_handle(t_data *data, t_token **head)
{
	t_token	*new_token;

	data->start = data->index + 1;
	new_token = create_token(NULL, PIPE);
	if (!new_token)
		return (data->exit_flag = 1, 1);
	append_token_lst(head, new_token);
	data->cmd_flag = 0;
	data->rd_flag = 0;
	return (0);
}
