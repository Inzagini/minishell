#include "minishell.h"

int	init_split(t_split *split, char **env, t_token **arg_list, t_token *arg)
{
	split->count_token = 0;
		split->expanded = expand_argument(arg->content, env);
	if (!split->expanded)
		return (1);
	split->split_tokens = ft_split(split->expanded, ' ');
	free(split->expanded);
	if (!split->split_tokens)
		return (1);
	while (split->split_tokens[split->count_token])
		split->count_token++;
	split->prev = find_previous_token(*arg_list, arg);
	split->next = arg->next;
	split->last_added = NULL;
	split->merge_prev = 0;
	if (split->prev)
		split->merge_prev = 1;
	split->merge_next = 0;
	if (split->next && arg->arg_group_id == split->next->arg_group_id)
		split->merge_next = 1;
	update_arg_ids(split, arg);
	return (0);
}

void	update_arg_ids(t_split *split, t_token *arg)
{
	split->update = split->next;
	while (split->update)
	{
		if (split->update->next
			&& split->update->arg_group_id == split->update->next->arg_group_id)
			split->update->arg_group_id = arg->arg_group_id
				+ split->count_token - split->merge_next - split->merge_prev;
		else
		{
			split->update->arg_group_id = arg->arg_group_id
				+ split->count_token - split->merge_next - split->merge_prev;
			split->count_token++;
		}
		split->update = split->update->next;
	}
}

int	split_argument(t_token **arg_list, t_token *arg, char **env, int arg_id)
{
	t_split	split;
	int		i;

	init_split(&split, env, arg_list, arg);
	i = -1;
	while (split.split_tokens[++i])
	{
		split.new_token = create_token_split(split.split_tokens[i], (arg_id)++);
		if (!split.new_token)
		{
			free_split(split.split_tokens);
			return (1);
		}
		if (i == 0 && split.prev)
		{
			merge_tokens(split.prev, split.new_token);
			split.last_added = split.prev;
		}
		else if (!split.split_tokens[i + 1] && split.next)
		{
			if (split.next->arg_group_id == arg->arg_group_id)
				merge_tokens(split.new_token, split.next);
			else
			{
				split.last_added->next = split.new_token;
				split.new_token->next = split.next;
			}
		}
		else
		{
			if (split.last_added)
				insert_token_after(arg_list, split.last_added, split.new_token);
			else
				insert_token_after(arg_list, arg, split.new_token);
			split.last_added = split.new_token;
		}
	}
	free_split(split.split_tokens);
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
	if (!after)
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

t_token *create_token_split(char *content, int arg_id)
	{
	t_token *new_token;

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
	new_token->quote_identifier = 0;
	new_token->next = NULL;
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
		return ;
	ft_strlcpy(merged_content, first->content, new_len);
	ft_strlcat(merged_content, second->content, new_len);
	free(first->content);
	first->content = merged_content;
	first->next = second->next;
	free(second->content);
	free(second);
}


