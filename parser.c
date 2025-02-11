/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:46:06 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/11 10:55:31 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parser(t_token *token_list, t_env *env)
{
	t_parser	parser;

	initialize_parser(&parser, token_list);
	while (parser.token)
	{
		if (parser.token->type == CMD || parser.token->type == ARG)
		{
			if (!add_argument_token(&parser))
				return (NULL);
		}
		else if (parser.token->type == SEP)
			parser.arg_group_id++;
		else if (handle_redirects(&parser, env) == 1)
			return (NULL);
		else if (parser.token->type == PIPE || parser.token->type == NEW_LINE)
		{
			if (handle_pipes(&parser) == 1)
				return (NULL);
		}
		handle_quote_flag(&parser, parser.token);
		parser.token = parser.token->next;
	}
	if (parser.size > 0 && cmdnew(&parser) == 1)
		return (NULL);
	return (parser.cmd_list);
}

void	initialize_parser(t_parser *parser, t_token *token_list)
{
	parser->new_cmd = NULL;
	parser->cmd_list = NULL;
	parser->arg_tokens = NULL;
	parser->token = token_list;
	parser->arg_tokens = NULL;
	parser->arg_group_id = 0;
	parser->id = 0;
	parser->size = 0;
	parser->redir_in = 0;
	parser->redir_out = 0;
	parser->redir_file_in = NULL;
	parser->redir_file_out = NULL;
	parser->heredoc_sep = NULL;
	parser->pipe_flag_in = 0;
	parser->pipe_flag_out = 0;
	parser->pipe_found = 0;
	parser->invalid_redirect_in = 0;
	parser->invalid_redirect_out = 0;
	parser->open_dquote = 0;
	parser->open_squote = 0;
}

void	reset_parser(t_parser *parser)
{
	parser->id++;
	parser->arg_group_id = 0;
	parser->size = 0;
	parser->redir_in = 0;
	parser->redir_out = 0;
	parser->redir_file_in = NULL;
	parser->redir_file_out = NULL;
	parser->heredoc_sep = NULL;
	parser->arg_tokens = NULL;
	parser->invalid_redirect_in = 0;
	parser->invalid_redirect_out = 0;
	parser->open_dquote = 0;
	parser->open_squote = 0;
}

int	add_argument_token(t_parser *parser)
{
	t_token	*new_token;
	t_token	*last;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (clean_parser(parser), 0);
	new_token->content = ft_strdup(parser->token->content);
	if (!new_token->content)
		return (clean_parser(parser), free(new_token), 0);
	set_quote_identifier(new_token, parser->token, parser);
	new_token->next = NULL;
	new_token->arg_group_id = parser->arg_group_id;
	new_token->arg_group_id_delta = 0;
	if (!parser->arg_tokens)
		parser->arg_tokens = new_token;
	else
	{
		last = parser->arg_tokens;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
	parser->size++;
	return (1);
}

