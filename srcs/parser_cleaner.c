/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:45:49 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:45:50 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_parser(t_parser *parser)
{
	if (parser->cmd_list)
		clean_commands(parser->cmd_list);
	if (parser->redir_file_in)
		free (parser->redir_file_in);
	if (parser->redir_file_out)
		free (parser->redir_file_out);
	if (parser->heredoc_sep)
		free (parser->heredoc_sep);
}

void	clean_commands(t_command *cmd_list)
{
	t_command	*curr_cmd;
	t_token		*temp;

	curr_cmd = cmd_list;
	while (curr_cmd)
	{
		free (curr_cmd->redir_file_in);
		free (curr_cmd->redir_file_out);
		if (curr_cmd->heredoc_separator)
			free (curr_cmd->heredoc_separator);
		if (curr_cmd->args)
			free_split(curr_cmd->args);
		if (curr_cmd->quotes)
			free (curr_cmd->quotes);
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
