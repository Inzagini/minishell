#include "minishell.h"

t_token	*create_token(char *content, t_token_type token_type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = token_type;
	new_token->content = content;
	new_token->quote_identifier = 0;
	new_token->arg_group_id = 0;
	new_token->previous = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	append_token_lst(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
	new_token->previous = tmp;
}

int	token_quotes(t_token **head, t_data *data, t_token_type type)
{
	t_token *new_token;

	new_token = create_token(NULL, type);
	if (!new_token)
		return (data->exit_flag = 1, 1);
	append_token_lst(head, new_token);
	return (0);
}
