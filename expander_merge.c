#include "minishell.h"

int	merge_arguments(t_command *cmd_list)
{
	t_command	*cmd;
	t_token		*arg;
	int			max;

	cmd = cmd_list;
	while (cmd)
	{
		cmd->size = calculate_size(cmd->arg_tokens);
		arg = cmd->arg_tokens;
		cmd->args = malloc ((cmd->size + 1) * sizeof (char *));
		if (!cmd->args)
			return (1);
		cmd->args[cmd->size] = NULL;
		max = -1;
		conduct_merge(arg, cmd, &max);
		cmd = cmd->next;
	}
	return (0);
}

int	conduct_merge(t_token *arg, t_command *cmd, int *max)
{
	char	*content;
	int		i;

	i = 0;
	while (arg)
	{

		if (!arg->content)
			content = ft_strdup("");
		else
			content = ft_strdup(arg->content);
		if (!content)
			return (1);
		if (arg->arg_group_id == *max)
		{
			i--;
			cmd->args[i] = ft_strjoin(cmd->args[i], content);
			if (!cmd->args[i])
				return (free (content), 1);
			i++;
		}
		else
		{
			cmd->args[i++] = content;
			*max = arg->arg_group_id;
		}
		arg = arg->next;
	}
	return (0);
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
