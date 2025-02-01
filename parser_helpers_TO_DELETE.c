#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

void print_command(t_command *cmd)
{
	t_token	*args;
	t_command *head;
	int i;

	head = cmd;

	while (cmd)
	{
		printf("Command ID: %d\n", cmd->id);
		printf("Command Name: %s\n", cmd->arg_tokens->content);
		printf("Builtin: %d\n", cmd->builtin_flag);
		printf("# of args: %d\n", cmd->size);
		printf("Arguments:\n");
		args = cmd->arg_tokens;
		printf("TOKENS\n");
		while (args)
		{
			printf("\t%s\t", args->content);
			printf("Quote ID: %d\t", args->quote_identifier);
			printf("Arg ID: %d\n", args->arg_group_id);
			args = args->next;
		}
		i = 0;
		printf("Arg Strings\n");
		while (cmd->args[i])
		{
			printf("\t\"%s\"\n", cmd->args[i]);
			i++;
		}
		i = 0;
		printf("Arg Quotes\n");
		while (cmd->quotes[i] != -1)
		{
			printf("\t%d\n", cmd->quotes[i]);
			i++;
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
		cmd = cmd->next;
	}
}

// c3a8c3% echo eabc$VAR"$VAR"$VAR'abc'
// eabcPAUL BUCHTERPAUL BUCHTERPAUL BUCHTERabc
