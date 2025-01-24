#include "minishell.h"

int	tokenizer(char *input, t_token **head, t_env *env)
{
	int i;

	i = 1;
	while (i)
	{
		if (token_construc(input, head))
		{
			clean_tokens(head);
			free(input);
			return (1);
		}
		i = check_tokens(&input, *head, env);
		if (i)
		{
			if (i == 2)
			{
				clean_tokens(head);
				return (1);
			}
		}
	}
	return (0);
}
