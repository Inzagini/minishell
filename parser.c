/*
	to do
		INVAL
		HEREDOC
		ERROR Handling (Malloc fails, input checks)

*/

#include "minishell.h"

t_command	*parser(t_token *token_list)
{
	t_parser	parser;

	initialize_parser(&parser, token_list);
	while (parser.curr_token)
	{
		if (parser.curr_token->type == CMD || parser.curr_token->type == ARG)
		{
			parser.args = add_argument(&parser);
			if (!parser.args)
				return (NULL);
		}
		if (handle_redirects(&parser) == 1)
				return (NULL);
		if (parser.curr_token->type == PIPE || parser.curr_token->type == NEW_LINE)
		{
			if (cmdnew(&parser) == 1)
				return (NULL);
			reset_parser(&parser);
		}
		if (parser.curr_token->type == SQUOTE || parser.curr_token->type == DQUOTE)
			handle_quotes(parser.curr_token, &parser);
		parser.curr_token = parser.curr_token->next;
	}
	if (parser.size > 0)
		if (cmdnew(&parser) == 1)
			return (NULL);
	return (parser.cmd_list);
}

int	handle_redirects(t_parser *parser)
{
	t_token_type	type;

	type = parser->curr_token->type;
	if (type == RD_OUT || type == RD_IN || type == RD_APP || type == RD_ININ)
	{
		if (parser->curr_token->next && parser->curr_token->next->type == SEP)
			parser->curr_token = parser->curr_token->next;
		if (parser->curr_token->next && parser->curr_token->next->type == ARG)
			parser->curr_token = parser->curr_token->next;
		else
			return (printf("syntax error: expected a argument after redirection\n")
				, clean_parser(parser), 1);
		if (set_redirects(parser, type) == 1)
			return (1);
	}
	return (0);
}

int	set_redirects(t_parser *parser, t_token_type type)
{
	if (type == RD_OUT)
	{
		parser->redir_file_out = ft_strdup(parser->curr_token->content);
		if (!parser->redir_file_out)
			return (clean_parser(parser), 1);
		parser->redir_out = 1;
	}
	else if (type == RD_IN)
	{
		parser->redir_file_in = ft_strdup(parser->curr_token->content);
		if (!parser->redir_file_in)
			return (clean_parser(parser), 1);
		parser->redir_in = 1;
	}
	else if (type == RD_APP)
	{
		parser->redir_file_out = ft_strdup(parser->curr_token->content);
		if (!parser->redir_file_out)
			return (clean_parser(parser), 1);
		parser->redir_out = 2;
	}
	else if (type == RD_ININ)
	{
		parser->heredoc_separator = ft_strdup(parser->curr_token->content);
		if (!parser->heredoc_separator)
			return (clean_parser(parser), 1);
		parser->redir_in = 2;
	}
	return (0);
}

void	handle_quotes(t_token *curr_token, t_parser *parser)
{
	if (curr_token->type == DQUOTE)
	{
		if (parser->double_quotes == 0)
			parser->double_quotes = 1;
		else
		{
			parser->quote_identifier[parser->size - 1] = 2;
			parser->double_quotes = 0;
		}
	}
	else if (curr_token->type == SQUOTE)
	{
		if (parser->single_quotes == 0)
			parser->single_quotes = 1;
		else
		{
			parser->quote_identifier[parser->size - 1] = 1;
			parser->single_quotes = 0;
		}
	}
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
	new_args[i] = ft_strdup(parser->curr_token->content);
	if (!new_args[i])
		return (clean_parser(parser), NULL);
	new_args[i + 1] = NULL;
	free(parser->args);
	(parser->size)++;
	return (new_args);
}

void	initialize_parser(t_parser *parser, t_token *token_list)
{
	int	i;

	parser->curr_token = token_list;
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

int	cmdnew(t_parser *parser)
{
	t_command	*new_cmd;
	int			i;

	new_cmd = malloc (sizeof(t_command));
	if (!new_cmd)
		return (clean_parser(parser), 1);
	new_cmd->id = parser->id;
	new_cmd->name = parser->args[0];
	new_cmd->arguments = parser->args;
	parser->args = NULL;
	new_cmd->redir_in = parser->redir_in;
	new_cmd->redir_out = parser->redir_out;
	new_cmd->redir_file_in = parser->redir_file_in;
	parser->redir_file_in = NULL;
	new_cmd->redir_file_out = parser->redir_file_out;
	parser->redir_file_out = NULL;
	new_cmd->heredoc_separator = parser->heredoc_separator;
	parser->heredoc_separator = NULL;
	new_cmd->size = parser->size;
	i = -1;
	while (++i < 100)
		new_cmd->quote_identifier[i] = parser->quote_identifier[i];
	new_cmd->next = NULL;
	parser->new_cmd = new_cmd;
	cmdadd_back(&parser->cmd_list, parser->new_cmd);
	return (0);
}

void	cmdadd_back(t_command **list, t_command *new)
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
