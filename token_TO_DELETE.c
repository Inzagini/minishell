#include "minishell.h"

void	print_tokens(t_token *token_list)
{
	t_token *head;

	head = token_list;
	while (token_list)
	{
		if (token_list->type == CMD)
			printf("[CMD]\n");
		else if (token_list->type == ARG)
			printf("[ARG]\n");
		else if (token_list->type == PIPE)
			printf("[PIPE]\n");
		else if (token_list->type == RD_OUT)
			printf("[RD_OUT]\n");
		else if (token_list->type == RD_IN)
			printf("[RD_IN]\n");
		else if (token_list->type == RD_APP)
			printf("[RD_APP]\n");
		else if (token_list->type == RD_HEREDOC)
			printf("[RD_HEREDOC]\n");
		else if (token_list->type == SEP)
			printf("[SEP]\n");
		else if (token_list->type == NEW_LINE)
			printf("[NEW_LINE]\n");
		token_list = token_list->next;
	}
}
