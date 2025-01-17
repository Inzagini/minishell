#include "minishell.h"

void	clean_parser(t_parser *parser)
{
	int	i;

	if (parser->cmd_list)
		clean_commands(parser->cmd_list);
	if (parser->redir_file_in)
		free (parser->redir_file_in);
	if (parser->redir_file_out)
		free (parser->redir_file_out);
	if (parser->heredoc_separator)
		free (parser->heredoc_separator);
	// if (parser->args)  NEED TO FREE THE ARG TOKEN LIST
	// {
	// 	i = -1;
	// 	while (parser->args[++i])
	// 		free (parser->args[i]);
	// 	free (parser->args);
	// }
}

void	clean_commands(t_command *cmd_list)
{
	t_command	*curr_cmd;
	t_token		*temp;

	curr_cmd = cmd_list;
	while (curr_cmd)
	{
		if (curr_cmd->redir_file_in)
			free (curr_cmd->redir_file_in);
		if (curr_cmd->redir_file_out)
			free (curr_cmd->redir_file_out);
		if (curr_cmd->heredoc_separator)
			free (curr_cmd->heredoc_separator);
		if (curr_cmd->args)
            free_split(curr_cmd->args);
        while (curr_cmd->arg_tokens)
		{
			temp = curr_cmd->arg_tokens;
			curr_cmd->arg_tokens = curr_cmd->arg_tokens->next;
			free (temp->content);
			free (temp);
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
