/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quannguy <quannguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:54:08 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/11 11:01:15 by quannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote_flag(t_parser *parser, t_token *token)
{
	if (token->type == SQUOTE)
	{
		if (parser->open_squote == 0)
			parser->open_squote = 1;
		else
			parser->open_squote = 0;
	}
	else if (token->type == DQUOTE)
	{
		if (parser->open_dquote == 0)
			parser->open_dquote = 1;
		else
			parser->open_dquote = 0;
	}
}

void	set_quote_identifier(t_token *new_token,
	t_token *current, t_parser *parser)
{
	if (current->previous && current->next
		&& (parser->open_squote == 1 || parser->open_dquote == 1))
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
