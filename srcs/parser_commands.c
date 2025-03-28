/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:45:53 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:45:54 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmdnew(t_parser *parser)
{
	t_command	*new_cmd;

	handle_pipe_flags(parser);
	new_cmd = malloc (sizeof(t_command));
	if (!new_cmd)
		return (clean_parser(parser), 1);
	new_cmd->id = parser->id;
	new_cmd->redir_in = parser->redir_in;
	new_cmd->redir_out = parser->redir_out;
	new_cmd->redir_file_in = parser->redir_file_in;
	new_cmd->redir_file_out = parser->redir_file_out;
	new_cmd->heredoc_separator = parser->heredoc_sep;
	new_cmd->size = parser->size;
	new_cmd->arg_tokens = parser->arg_tokens;
	new_cmd->env = NULL;
	new_cmd->builtin_flag = 0;
	new_cmd->next = NULL;
	new_cmd->quotes = NULL;
	parser->new_cmd = new_cmd;
	cmdadd(&parser->cmd_list, parser->new_cmd);
	return (reset_parser(parser), 0);
}

void	cmdadd(t_command **list, t_command *new)
{
	t_command	*temp;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	handle_pipe_flags(t_parser *parser)
{
	if (parser->pipe_flag_in == 1)
	{
		if (parser->redir_in == 0)
		{
			parser->redir_in = 3;
			free(parser->redir_file_in);
			parser->redir_file_in = NULL;
		}
	}
	if (parser->pipe_found == 1 || parser->pipe_flag_out == 1)
	{
		if (parser->redir_out == 0)
		{
			parser->redir_out = 3;
			free(parser->redir_file_out);
			parser->redir_file_out = NULL;
			if (parser->pipe_found == 1)
				parser->pipe_flag_in = 1;
		}
	}
	parser->pipe_found = 0;
}

int	handle_pipes(t_parser *parser)
{
	if (parser->token->type == PIPE)
	{
		parser->pipe_found = 1;
	}
	if (cmdnew(parser) == 1)
		return (1);
	if (parser->token->type == NEW_LINE)
		parser->pipe_flag_in = 0;
	return (0);
}

void	update_arg_id_deltas(t_token *input)
{
	t_token	*tokens;

	tokens = input;
	while (tokens)
	{
		if (tokens->next
			&& tokens->next->arg_group_id > tokens->arg_group_id)
			tokens->next->arg_group_id_delta = 1;
		tokens = tokens->next;
	}
}
