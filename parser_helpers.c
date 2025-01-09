#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

void print_command(t_command *cmd)
{
    int i;
	if (!cmd)
        return;
    printf("Command ID: %d\n", cmd->id);
    printf("Command Name: %s\n", cmd->name);
    printf("Arguments:\n");
    for (int i = 0; cmd->arguments[i]; i++)
        printf("  %s\n", cmd->arguments[i]);
    printf("Redirection In: %d\n", cmd->redir_in);
    printf("Redirection Out: %d\n", cmd->redir_out);
    if (cmd->redir_file_in)
		printf("Redirection File: %s\n", cmd->redir_file_in);
	if (cmd->redir_file_out)
		printf("Redirection File: %s\n", cmd->redir_file_out);
	i = -1;
	while (++i < cmd->size)
		printf("Quote identifier[%d]: %d\n", i, cmd->quote_identifier[i]);
    printf("---------------\n");
}

void free_tokens(t_token *token_list)
{
    t_token *temp;
    while (token_list)
    {
        temp = token_list;
        token_list = token_list->next;
        free(temp->content);
        free(temp);
    }
}

void free_commands(t_command *cmd_list)
{
    t_command *temp;
    while (cmd_list)
    {
        temp = cmd_list;
        cmd_list = cmd_list->next;
        if (temp->arguments)
        {
            for (int i = 0; temp->arguments[i]; i++)
                free(temp->arguments[i]);
            free(temp->arguments);
        }
        if (temp->redir_file_in)
            free(temp->redir_file_in);
		if (temp->redir_file_out)
            free(temp->redir_file_out);
        free(temp);
    }
}
