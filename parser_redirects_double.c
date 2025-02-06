/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects_double.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quannguy <quannguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:45:56 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/06 09:38:53 by quannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_redirects_double(t_parser *parser, t_token_type type)
{
	if (type == RD_APP && parser->invalid_redirect_out == 0)
	{
		return (set_redirect_append(parser));
	}
	else if (type == RD_HEREDOC)
	{
		parser->heredoc_sep = ft_strdup(parser->token->content);
		while (parser->token->next && (parser->token->next->type == ARG
				|| parser->token->next->type == DQUOTE
				|| parser->token->next->type == SQUOTE))
		{
			parser->heredoc_sep = ft_strjoin_gnl(parser->heredoc_sep,
					parser->token->next->content);
			parser->token = parser->token->next;
		}
		if (!parser->heredoc_sep)
			return (clean_parser(parser), 1);
		parser->redir_in = 2;
	}
	return (0);
}

int	set_redirect_append(t_parser *parser)
{
	int	fd;

	parser->redir_file_out = ft_strdup(parser->token->content);
	while (parser->token->next && (parser->token->next->type == ARG
			|| parser->token->next->type == DQUOTE
			|| parser->token->next->type == SQUOTE))
	{
		parser->redir_file_out
			= ft_strjoin_gnl(parser->redir_file_out,
				parser->token->next->content);
		parser->token = parser->token->next;
	}
	if (!parser->redir_file_out)
		return (clean_parser(parser), 1);
	parser->redir_out = 2;
	fd = open(parser->redir_file_out, O_TRUNC
			| O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		parser->invalid_redirect_out = 1;
	if (fd > 0)
		close (fd);
	return (0);
}
