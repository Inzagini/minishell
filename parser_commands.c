#include "minishell.h"

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
	new_cmd->redir_in = parser->redir_in;
	new_cmd->redir_out = parser->redir_out;
	new_cmd->redir_file_in = parser->redir_file_in;
	new_cmd->redir_file_out = parser->redir_file_out;
	new_cmd->heredoc_separator = parser->heredoc_separator;
	new_cmd->size = parser->size;
	i = -1;
	while (++i < 100)
		new_cmd->quote_identifier[i] = parser->quote_identifier[i];
	new_cmd->next = NULL;
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
