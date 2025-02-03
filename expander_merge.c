#include "minishell.h"

int	merge_arguments(t_command *cmd_list)
{
	t_command	*cmd;
	t_token		*arg;
	int			max;
	int			i;

	cmd = cmd_list;
	while (cmd)
	{
		cmd->size = calculate_size(cmd->arg_tokens);
		arg = cmd->arg_tokens;
		cmd->args = malloc ((cmd->size + 1) * sizeof (char *));
		if (!cmd->args)
			return (1);
		cmd->quotes = malloc ((cmd->size + 1) * sizeof (int));
		if (!cmd->quotes)
			return (free(cmd->args), 1);
		cmd->args[cmd->size] = NULL;
		cmd->quotes[cmd->size] = -1;
		max = -1;
		i = 0;
		conduct_merge(arg, cmd, &max, i);
		cmd = cmd->next;
	}
	return (0);
}

void	conduct_merge(t_token *arg, t_command *cmd, int *max, int i)
{
	char	*content;

	while (arg)
	{
		if (!arg->content)
			content = ft_strdup("");
		else
			content = ft_strdup(arg->content);
		if (arg->arg_group_id == *max)
		{
			i--;
			cmd->args[i] = ft_strjoin(cmd->args[i], content);
			if (!cmd->args[i])
				free (content);
		}
		else
		{
			cmd->args[i] = content;
			*max = arg->arg_group_id;
		}
		cmd->quotes[i++] = arg->quote_identifier;
		arg = arg->next;
	}
}

int	calculate_size(t_token *token)
{
	int	size;
	int	max;

	size = 0;
	max = -1;
	while (token)
	{
		if (token->arg_group_id > max)
			size++;
		max = token->arg_group_id;
		token = token->next;
	}
	return (size);
}
