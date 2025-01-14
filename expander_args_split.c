#include "minishell.h"
#include <string.h>

int	split_argument(t_token **arg_list, t_token *arg, char **env, int arg_id)
{
	char	*expanded;
	char	**split_tokens;
	int		i;
	int		k;
	t_token	*prev;
	t_token	*next;
	t_token	*last_added;
	t_token	*update;
	t_token	*new_token;
	int		merge_with_prev;
	int		merge_with_next;

	expanded = expand_argument(arg->content, env);
	if (!expanded)
		return (1);
	split_tokens = ft_split(expanded, ' ');
	free(expanded);
	if (!split_tokens)
		return (1);
	k = 0;
	while (split_tokens[k])
		k++;
	prev = find_previous_token(*arg_list, arg);
	next = arg->next;
	last_added = NULL;
	merge_with_prev = 0;
	if (prev)
		merge_with_prev = 1;
	merge_with_next = 0;
	if (next && arg->arg_group_id == next->arg_group_id)
		merge_with_next = 1;

	update = next;
	while (update)
	{
		if (update->next && update->arg_group_id == update->next->arg_group_id)
			update->arg_group_id = arg->arg_group_id + k - merge_with_next - merge_with_prev;
		else
		{
			update->arg_group_id = arg->arg_group_id + k - merge_with_next - merge_with_prev;
			k++;
		}
		update = update->next;
	}
	for (int i = 0; split_tokens[i]; i++)
	{
		new_token = create_token2(split_tokens[i], (arg_id)++);
		if (!new_token)
		{
			free_split(split_tokens);
			return (1);
		}
		if (i == 0 && prev)
		{
			merge_tokens(prev, new_token);
			last_added = prev;
		}
		else if (!split_tokens[i + 1] && next)
		{
			if (next->arg_group_id == arg->arg_group_id)
				merge_tokens(new_token, next);
			else
			{
				last_added->next = new_token;
				new_token->next = next;
			}
		}
		else
		{
			if (last_added)
				insert_token_after(arg_list, last_added, new_token);
			else
				insert_token_after(arg_list, arg, new_token);
			last_added = new_token;
		}
	}
	free_split(split_tokens);
	remove_token(arg_list, arg);
	return (0);
}

int expand_arguments_noquote(t_env *env, t_command *cmd_list)
{
	t_token *arg;

	while (cmd_list)
	{
		arg = cmd_list->arg_tokens;
		while (arg)
		{
			if (arg->quote_identifier == 0 && ft_strchr(arg->content, '$') != NULL) // Unquoted
			{
				if (split_argument(&cmd_list->arg_tokens, arg, env->env_current, arg->arg_group_id))
					return (1);
			}
			arg = arg->next;
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}

	void free_split(char **split_tokens)
	{
	if (!split_tokens)
		return;
	for (int i = 0; split_tokens[i]; i++)
		free(split_tokens[i]);
	free(split_tokens);
	}

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

void insert_token_after(t_token **arg_list, t_token *after, t_token *new_token)
{
	if (!new_token)
		return;
	if (!after) // Insert at the head of the list
	{
		new_token->next = *arg_list;
		*arg_list = new_token;
	}
	else
	{
		new_token->next = after->next;
		after->next = new_token;
	}
	}

t_token *create_token2(char *content, int arg_id)
	{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(content); // Duplicate the content
	if (!new_token->content)
	{
		free(new_token);
		return (NULL);
	}
	new_token->arg_group_id = arg_id;
	new_token->quote_identifier = 0;	// Default to unquoted
	new_token->next = NULL;				// Initialize the next pointer to NULL
	return (new_token);
	}

t_token *find_previous_token(t_token *arg_list, t_token *token)
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

void merge_tokens(t_token *first, t_token *second)
{
	size_t	new_len;
	char	*merged_content;

	if (!first || !second)
		return ;
	new_len = ft_strlen(first->content) + ft_strlen(second->content) + 1;
	merged_content = malloc(new_len);
	if (!merged_content)
		return;
	strcpy(merged_content, first->content); //replace with new function
	strcat(merged_content, second->content); //replace with new function
	free(first->content);
	first->content = merged_content;
	first->next = second->next;
	free(second->content);
	free(second);
}


