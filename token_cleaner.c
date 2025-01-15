#include "minishell.h"

void	clean_tokens(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->content);
		(*head)->content = NULL;
		free((*head));
		*head = tmp;
	}
	*head = NULL;
	head = NULL;
}
