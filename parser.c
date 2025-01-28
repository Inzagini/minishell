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
	parser->heredoc_separator = NULL;
	parser->pipe_flag_in = 0;
	parser->pipe_flag_out = 0;
	parser->pipe_found = 0;
	parser->invalid_redirect_in = 0;
	parser->invalid_redirect_out = 0;
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
	parser->heredoc_separator = NULL;
	parser->arg_tokens = NULL;
	parser->invalid_redirect_in = 0;
	parser->invalid_redirect_out = 0;
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
	set_quote_identifier(new_token, parser->token);
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

void	set_quote_identifier(t_token *new_token, t_token *current)
{
	if (current->previous && current->next)
	{
		if (current->previous->type == SQUOTE && current->next->type == SQUOTE)
			new_token->quote_identifier = 1;
		else if (current->previous->type
			== DQUOTE && current->next->type == DQUOTE)
			new_token->quote_identifier = 2;
		else
			new_token->quote_identifier = 0;
	}
	else
		new_token->quote_identifier = 0;
}

