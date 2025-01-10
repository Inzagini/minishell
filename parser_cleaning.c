#include "minishell.h"

void	clean_parser(t_parser *parser)
{
	int	i;

	clean_commands(parser->cmd_list);
	if (parser->redir_file_in)
		free (parser->redir_file_in);
	if (parser->redir_file_out)
		free (parser->redir_file_out);
	if (parser->args)
	{
		i = -1;
		while (parser->args[++i])
			free (parser->args[i]);
		free (parser->args);
	}
}

void	clean_commands(t_command *cmd_list)
{
	t_command	*curr_cmd;
	int			i;

	curr_cmd = cmd_list;
	while (curr_cmd)
	{
		if (curr_cmd->redir_file_in)
			free (curr_cmd->redir_file_in);
		if (curr_cmd->redir_file_out)
			free (curr_cmd->redir_file_out);
		if (curr_cmd->arguments)
		{
			i = -1;
			while (curr_cmd->arguments[++i])
				free (curr_cmd->arguments[i]);
			free (curr_cmd->arguments);
		}
		curr_cmd = curr_cmd->next;
	}
	clean_cmd_list(&cmd_list);
}

void	clean_cmd_list(t_command **cmd_list)
{
	t_command	*temp;
	t_command	*temp2;

	if (!cmd_list)
		return ;
	temp = *cmd_list;
	while (temp)
	{
		temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
	*cmd_list = NULL;
}
