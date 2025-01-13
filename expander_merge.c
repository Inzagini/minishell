#include "minishell.h"

int	merge_arguments(t_command *cmd_list)
{
	t_command	*cmd;
	t_token		*arg;
	int			i;
	int			max;
	char		*content;
	char		*temp;

	cmd = cmd_list;
	while (cmd)
	{
		cmd->size = calculate_size(cmd->arg_tokens);
		arg = cmd->arg_tokens;
		cmd->args = malloc ((cmd->size + 1) * sizeof (char *));
		if (!cmd->args)
			return (1); //needs more cleanup
		cmd->args[cmd->size] = NULL;
		i = 0;
		max = -1;
		while (arg)
		{
			content = ft_strdup(arg->content);
			if (!content)	//clean up
				return (1);
			if (arg->arg_group_id == max)
			{
				i--;
				cmd->args[i] = ft_strjoin(cmd->args[i], content); //needs protection
				i++;
			}
			else
			{
				cmd->args[i++] = content;
				max = arg->arg_group_id;
			}
			arg = arg->next;
		}
		cmd = cmd->next;
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
