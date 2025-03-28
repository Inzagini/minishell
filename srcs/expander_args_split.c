/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_args_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:43:27 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/06 12:40:38 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_split(t_split *split, char **env, t_token **arg_list, t_token *arg)
{
	split->count_token = 0;
	split->expanded = expand_argument(arg->content, env, split->expanded);
	if (!split->expanded)
		return (1);
	split->split_tokens = ft_split(split->expanded, ' ');
	free(split->expanded);
	if (!split->split_tokens || !split->split_tokens[0])
		return (free (arg->content), free(split->split_tokens), 1);
	while (split->split_tokens[split->count_token])
		split->count_token++;
	if (split->count_token == 1)
		return (free(arg->content), 0);
	split->prev = find_previous_token(*arg_list, arg);
	split->next = arg->next;
	split->last_added = NULL;
	split->merge_prev = 0;
	if ((split->prev || arg->content[0] != '$') || !split->prev)
		split->merge_prev = 1;
	split->merge_next = 0;
	if (split->next && arg->arg_group_id == split->next->arg_group_id)
		split->merge_next = 1;
	free(arg->content);
	arg->content = NULL;
	update_arg_ids(split, arg);
	return (0);
}

void	update_arg_ids(t_split *split, t_token *arg)
{
	int	base_id;
	int	new_id;

	base_id = arg->arg_group_id;
	new_id = base_id + split->count_token
		- split->merge_prev - split->merge_next + 1;
	if (split->count_token == 0)
		new_id = base_id;
	split->update = split->next;
	while (split->update)
	{
		split->update->arg_group_id = new_id;
		if (split->update->next && split->update->next->arg_group_id_delta == 1)
			new_id = new_id + 1;
		split->update = split->update->next;
	}
}

int	expand_arguments_noquote(t_env *env, t_command *cmd_list)
{
	t_token	*arg;
	t_token	*next_arg;

	while (cmd_list)
	{
		arg = cmd_list->arg_tokens;
		update_arg_id_deltas(arg);
		while (arg)
		{
			next_arg = arg->next;
			if (arg->quote_identifier == 0
				&& ft_strchr(arg->content, '$') != NULL)
			{
				if (split_argument(&cmd_list->arg_tokens, arg,
						env->env, arg->arg_group_id))
					return (1);
			}
			arg = next_arg;
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}

int	handle_token_merge(t_split *split, t_token *arg, t_token **arg_list, int i)
{
	if (i == 0 && split->prev)
	{
		merge_tokens(split->prev, split->new_token);
		split->last_added = split->prev;
	}
	else if (!split->split_tokens[i + 1] && split->next)
	{
		if (split->next->arg_group_id == arg->arg_group_id)
			merge_tokens(split->new_token, split->next);
		else
			split->new_token->next = split->next;
		split->last_added->next = split->new_token;
	}
	else
	{
		if (split->last_added)
			insert_token_after(arg_list, split->last_added, split->new_token);
		else
			insert_token_after(arg_list, arg, split->new_token);
		split->last_added = split->new_token;
	}
	return (0);
}

int	split_argument(t_token **arg_list, t_token *arg, char **env, int arg_id)
{
	t_split	split;
	int		i;

	if (init_split(&split, env, arg_list, arg) == 1)
		return (arg->content = NULL, 0);
	if (split.count_token == 1)
		return (arg->content = ft_strdup(split.split_tokens[0]),
			free_split(split.split_tokens), 0);
	i = -1;
	while (split.count_token > 0 && split.split_tokens[++i])
	{
		split.new_token = create_token_split(split.split_tokens[i], arg_id++);
		if (!split.new_token)
			return (free_split(split.split_tokens), 1);
		handle_token_merge(&split, arg, arg_list, i);
	}
	free_split(split.split_tokens);
	remove_token(arg_list, arg);
	return (0);
}
