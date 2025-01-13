#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

void print_command(t_command *cmd)
{
	t_token	*args;

	if (!cmd)
		return;
	printf("Command ID: %d\n", cmd->id);
	printf("Command Name: %s\n", cmd->arg_tokens->content);
	printf("Builtin: %d\n", cmd->builtin_flag);
	printf("Arguments:\n");
	args = cmd->arg_tokens;
	while (args)
	{
		printf("\t%s\n", args->content);
		args = args->next;
	}
	printf("Redirection In: %d\n", cmd->redir_in);
	printf("Redirection Out: %d\n", cmd->redir_out);
	if (cmd->redir_file_in)
		printf("Redirection IN File: %s\n", cmd->redir_file_in);
	if (cmd->redir_file_out)
		printf("Redirection OUT File: %s\n", cmd->redir_file_out);
	if (cmd->heredoc_separator)
		printf("Heredoc separator: %s\n", cmd->heredoc_separator);
	printf("---------------\n");
}
