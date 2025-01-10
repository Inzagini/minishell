#include "minishell.h"

t_command	*parser(t_token *token_list)
{
	t_parser	parser;

	initialize_parser(&parser, token_list);
	while (parser.token)
	{
		if (parser.token->type == CMD || parser.token->type == ARG)
		{
			parser.args = add_argument(&parser);
			if (!parser.args)
				return (NULL);
		}
		else if (handle_redirects(&parser) == 1)
			return (NULL);
		else if (parser.token->type == PIPE || parser.token->type == NEW_LINE)
		{
			if (cmdnew(&parser) == 1)
				return (NULL);
		}
		else if (parser.token->type == SQUOTE || parser.token->type == DQUOTE)
			handle_quotes(parser.token, &parser);
		parser.token = parser.token->next;
	}
	if (parser.size > 0 && cmdnew(&parser) == 1)
		return (NULL);
	return (parser.cmd_list);
}

void	initialize_parser(t_parser *parser, t_token *token_list)
{
	int	i;

	parser->token = token_list;
	parser->cmd_list = NULL;
	parser->args = NULL;
	parser->id = 0;
	parser->size = 0;
	parser->redir_in = 0;
	parser->redir_out = 0;
	parser->redir_file_in = NULL;
	parser->redir_file_out = NULL;
	parser->heredoc_separator = NULL;
	parser->single_quotes = 0;
	parser->double_quotes = 0;
	i = -1;
	while (++i < 100)
		parser->quote_identifier[i] = 0;
}

void	reset_parser(t_parser *parser)
{
	int	i;

	parser->id++;
	parser->args = NULL;
	parser->size = 0;
	parser->redir_in = 0;
	parser->redir_out = 0;
	parser->redir_file_in = NULL;
	parser->redir_file_out = NULL;
	parser->heredoc_separator = NULL;
	parser->single_quotes = 0;
	parser->double_quotes = 0;
	i = -1;
	while (++i < 100)
		parser->quote_identifier[i] = 0;
}

char	**add_argument(t_parser *parser)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (parser->size + 2));
	if (!new_args)
		return (clean_parser(parser), NULL);
	i = -1;
	while (++i < parser->size)
		new_args[i] = parser->args[i];
	new_args[i] = ft_strdup(parser->token->content);
	if (!new_args[i])
		return (clean_parser(parser), NULL);
	new_args[i + 1] = NULL;
	free(parser->args);
	(parser->size)++;
	return (new_args);
}
