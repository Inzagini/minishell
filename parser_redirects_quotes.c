#include "minishell.h"

int	handle_redirects(t_parser *parser)
{
	t_token_type	type;

	type = parser->token->type;
	if (type == RD_OUT || type == RD_IN
		|| type == RD_APP || type == RD_HEREDOC)
	{
		if (parser->token->next && parser->token->next->type == SEP)
			parser->token = parser->token->next;
		if (parser->token->next && parser->token->next->type == ARG)
			parser->token = parser->token->next;
		else
			return (printf("syntax error: expected ARG after redirection\n")
				, clean_parser(parser), 1);
		if (set_redirects_single(parser, type) == 1)
			return (1);
		if (set_redirects_double(parser, type) == 1)
			return (1);
	}
	return (0);
}

int	set_redirects_single(t_parser *parser, t_token_type type)
{
	if (type == RD_OUT)
	{
		parser->redir_file_out = ft_strdup(parser->token->content);
		if (!parser->redir_file_out)
			return (clean_parser(parser), 1);
		parser->redir_out = 1;
	}
	else if (type == RD_IN)
	{
		parser->redir_file_in = ft_strdup(parser->token->content);
		if (!parser->redir_file_in)
			return (clean_parser(parser), 1);
		parser->redir_in = 1;
	}
	return (0);
}

int	set_redirects_double(t_parser *parser, t_token_type type)
{
	if (type == RD_APP)
	{
		parser->redir_file_out = ft_strdup(parser->token->content);
		if (!parser->redir_file_out)
			return (clean_parser(parser), 1);
		parser->redir_out = 2;
	}
	else if (type == RD_HEREDOC)
	{
		parser->heredoc_separator = ft_strdup(parser->token->content);
		if (!parser->heredoc_separator)
			return (clean_parser(parser), 1);
		parser->redir_in = 2;
	}
	return (0);
}
