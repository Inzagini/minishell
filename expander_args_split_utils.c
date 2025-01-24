#include "minishell.h"

void	remove_token(t_token **arg_list, t_token *token)
{
	t_token	*prev;

	if (!arg_list || !*arg_list || !token)
		return ;
	if (*arg_list == token)
	{
		*arg_list = token->next;
	}
	else
	{
		prev = *arg_list;
		while (prev && prev->next != token)
			prev = prev->next;
		if (prev)
			prev->next = token->next;
	}
	free(token->content);
	free(token);
}

void	insert_token_after(t_token **arg_list, t_token *after, t_token *new)
{
	if (!new)
		return ;
	if (!after)
	{
		new->next = *arg_list;
		*arg_list = new;
	}
	else
	{
		new->next = after->next;
		after->next = new;
	}
}

t_token	*create_token_split(char *content, int arg_id)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(content);
	if (!new_token->content)
	{
		free(new_token);
		return (NULL);
	}
	new_token->arg_group_id = arg_id;
	new_token->arg_group_id_delta = 0;
	new_token->quote_identifier = 0;
	new_token->next = NULL;
	return (new_token);
}

t_token	*find_previous_token(t_token *arg_list, t_token *token)
{
	t_token	*current;

	if (!arg_list || !token || arg_list == token)
		return (NULL);
	current = arg_list;
	while (current && current->next != token)
		current = current->next;
	if (current->arg_group_id == token->arg_group_id)
		return (current);
	return (NULL);
}

void	merge_tokens(t_token *first, t_token *second)
{
	size_t	new_len;
	char	*merged_content;

	if (!first || !second)
		return ;
	new_len = ft_strlen(first->content) + ft_strlen(second->content) + 1;
	merged_content = malloc(new_len);
	if (!merged_content)
		return ;
	ft_strlcpy(merged_content, first->content, new_len);
	ft_strlcat(merged_content, second->content, new_len);
	free(first->content);
	first->content = merged_content;
	first->next = second->next;
	free(second->content);
	free(second);
}
