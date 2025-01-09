/*
	to do
		SQUOTE, DQUOTE
		LPAREN, RPAREN
		ENV_VAR
		INVAL
		HEREDOC
		ERROR Handling (Malloc fails, input checks)
*/

#include "minishell.h"

t_command	*parser(t_token *token_list)
{
	t_parser	parser;

	initialize_parser(&parser);
	parser.curr_token = token_list;
	while (parser.curr_token)
	{
		if (parser.curr_token->type == CMD || parser.curr_token->type == ARG)
			parser.args = add_argument(parser.args, &parser.size, parser.curr_token->content); //needs error handling
		if (parser.curr_token->type == RD_OUT || parser.curr_token->type == RD_IN
			|| parser.curr_token->type == RD_APP || parser.curr_token->type == RD_ININ)
		{
			if (!parser.curr_token->next || !parser.curr_token->next->next || parser.curr_token->next->next->type != ARG)
				return (printf("syntax error: expected a file after redirection\n"), NULL); //needs error handling (free allocated memory)
			else
				parser.curr_token = parser.curr_token->next->next;
			if (parser.curr_token->previous->previous->type == RD_OUT)
			{
				parser.redir_file_out = ft_strdup(parser.curr_token->content); //needs error handling (free allocated memory)
				parser.redir_out = 1;  // Output redirection
			}
			else if (parser.curr_token->previous->previous->type == RD_IN)
			{
				parser.redir_in = 1;   // Input redirection
				parser.redir_file_in = ft_strdup(parser.curr_token->content); //needs error handling (free allocated memory)
			}
			else if (parser.curr_token->previous->previous->type == RD_APP)
			{
				parser.redir_file_out = ft_strdup(parser.curr_token->content); //needs error handling (free allocated memory)
				parser.redir_out = 2;  // Append redirection
			}
			else if (parser.curr_token->previous->previous->type == RD_ININ)
				parser.redir_in = 2;	// Here-document redirection
		}
		if (parser.curr_token->type == PIPE || parser.curr_token->type == NEW_LINE)
		{
			parser.new_cmd = cmdnew(&parser); //needs error handling (free allocated memory)
			cmdadd_back(&parser.cmd_list, parser.new_cmd);
			reset_parser(&parser);
		}
		parser.curr_token = parser.curr_token->next;
	}
	if (parser.size > 0)
	{
		parser.new_cmd = cmdnew(&parser); //needs error handling (free allocated memory)
		cmdadd_back(&parser.cmd_list, parser.new_cmd);
	}
	return (parser.cmd_list);
}

char	**add_argument(char **args, int *size, const char *arg)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (*size + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < *size)
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	free(args);
	(*size)++;
	return (new_args);
}

void	initialize_parser(t_parser *parser)
{
	parser->curr_token = NULL;
	parser->cmd_list = NULL;
	parser->args = NULL;
	parser->id = 0;
	parser->size = 0;
	parser->redir_in = 0;
	parser->redir_out = 0;
	parser->redir_file_in = NULL;
	parser->redir_file_out = NULL;
}

void	reset_parser(t_parser *parser)
{
	parser->id++;
	parser->args = NULL;
	parser->size = 0;
	parser->redir_in = 0;
	parser->redir_out = 0;
	parser->redir_file_in = NULL;
	parser->redir_file_out = NULL;
}

t_command	*cmdnew(t_parser *parser)
{
	t_command	*new_cmd;

	new_cmd = malloc (sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->id = parser->id;
	new_cmd->name = parser->args[0];
	new_cmd->arguments = parser->args;
	new_cmd->redir_in = parser->redir_in;
	new_cmd->redir_out = parser->redir_out;
	new_cmd->redir_file_in = parser->redir_file_in;
	new_cmd->redir_file_out = parser->redir_file_out;
	new_cmd->next = NULL;
	return (new_cmd);
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
