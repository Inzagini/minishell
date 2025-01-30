#include "minishell.h"

int	handle_redirects(t_parser *parser, t_env *env)
{
	t_token_type	type;

	type = parser->token->type;
	if (type == RD_OUT || type == RD_IN
		|| type == RD_APP || type == RD_HEREDOC)
	{
		while (parser->token->next && (parser->token->next->type == SEP
				||  parser->token->next->type == DQUOTE
				|| parser->token->next->type == SQUOTE))
			parser->token = parser->token->next;
		if (parser->token->next && parser->token->next->type == ARG)
			parser->token = parser->token->next;
		else
			return (print_err(ft_get("SHELL", env->env), "syntax error", "expected ARG after redirection")
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
	int		fd;

	if (type == RD_OUT && parser->invalid_redirect_out == 0 && parser->invalid_redirect_in == 0)
	{
		parser->redir_file_out = ft_strdup(parser->token->content);
		while (parser->token->next && (parser->token->next->type == ARG || parser->token->next->type == DQUOTE || parser->token->next->type == SQUOTE))
		{
			parser->redir_file_out = ft_strjoin_gnl(parser->redir_file_out, parser->token->next->content);
			parser->token = parser->token->next;
		}
		if (!parser->redir_file_out)
			return (clean_parser(parser), 1);
		parser->redir_out = 1;
		fd = open(parser->redir_file_out, O_TRUNC
			| O_CREAT | O_WRONLY, 0644);
		if ((access(parser->redir_file_out, F_OK) == -1) || (access(parser->redir_file_out, W_OK) == -1))
			parser->invalid_redirect_out = 1;
		close (fd);
	}
	else if (type == RD_IN && parser->invalid_redirect_in == 0)
	{
		parser->redir_file_in = ft_strdup(parser->token->content);
		while (parser->token->next && (parser->token->next->type == ARG || parser->token->next->type == DQUOTE || parser->token->next->type == SQUOTE))
		{
			parser->redir_file_in = ft_strjoin_gnl(parser->redir_file_in, parser->token->next->content);
			parser->token = parser->token->next;
		}
		if (!parser->redir_file_in)
			return (clean_parser(parser), 1);
		parser->redir_in = 1;
		if (access(parser->redir_file_in, F_OK) == -1
			|| access(parser->redir_file_in, R_OK) == -1)
		{
			parser->invalid_redirect_in = 1;
		}
	}
	return (0);
}

int	set_redirects_double(t_parser *parser, t_token_type type)
{
	int	fd;

	if (type == RD_APP && parser->invalid_redirect_out == 0)
	{
		parser->redir_file_out = ft_strdup(parser->token->content);
		while (parser->token->next && (parser->token->next->type == ARG || parser->token->next->type == DQUOTE || parser->token->next->type == SQUOTE))
		{
			parser->redir_file_out = ft_strjoin_gnl(parser->redir_file_out, parser->token->next->content);
			parser->token = parser->token->next;
		}
		if (!parser->redir_file_out)
			return (clean_parser(parser), 1);
		parser->redir_out = 2;
		fd = open(parser->redir_file_out, O_TRUNC
			| O_CREAT | O_WRONLY, 0644);
		if (fd < 0)
			parser->invalid_redirect_out = 1;
		close (fd);
	}
	else if (type == RD_HEREDOC)
	{
		parser->heredoc_separator = ft_strdup(parser->token->content);
		while (parser->token->next && (parser->token->next->type == ARG || parser->token->next->type == DQUOTE || parser->token->next->type == SQUOTE))
		{
			parser->heredoc_separator = ft_strjoin_gnl(parser->heredoc_separator, parser->token->next->content);
			parser->token = parser->token->next;
		}
		if (!parser->heredoc_separator)
			return (clean_parser(parser), 1);
		parser->redir_in = 2;
	}
	return (0);
}
