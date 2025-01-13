#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

void print_command(t_command *cmd)
{
	int i;

	if (!cmd)
		return;
	while (cmd)
	{
		printf("Command ID: %d\n", cmd->id);
		printf("Command Name: %s\n", cmd->arguments[0]);
		printf("Builtin: %d\n", cmd->builtin_flag);
		printf("Arguments:\n");
		for (int i = 0; cmd->arguments[i]; i++)
			printf("  %s\n", cmd->arguments[i]);
		printf("Redirection In: %d\n", cmd->redir_in);
		printf("Redirection Out: %d\n", cmd->redir_out);
		if (cmd->redir_file_in)
			printf("Redirection IN File: %s\n", cmd->redir_file_in);
		if (cmd->redir_file_out)
			printf("Redirection OUT File: %s\n", cmd->redir_file_out);
		if (cmd->heredoc_separator)
			printf("Heredoc separator: %s\n", cmd->heredoc_separator);
		i = -1;
		while (++i < cmd->size)
			printf("Quote identifier[%d]: %d\n", i, cmd->quote_identifier[i]);
		printf("---------------\n");
		cmd = cmd->next;
	}
}
