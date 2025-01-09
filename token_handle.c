#include "minishell.h"

int	sep_handle(char *str, int index, t_token **head)
{
	t_token	*new_token;

	printf("[SEP]\n");
	new_token = create_token(NULL, SEP);
	if (!new_token)
		return (1);
	append_token_lst(head, new_token);
	return (0);
}

int	pipe_handle(char *str, int index, t_token **head)
{
	t_token	*new_token;

	printf("[PIPE]\n");
	(*index)++;
	new_token = create_token(NULL, PIPE);
	if (!new_token)
		return (1);
	append_token_lst(head, new_token);
	return (0);
}

int	squote_handle(char *str, int index, t_token **head)
{
	t_token	*new_token;
	int		start;

	printf("[SQUOTE]\n");
	// new_token = create_token(NULL, SQUOTE);
	// if (!new_token)
	// 	return (1);
	// append_token_list(head, new_token);
	start = ++index;
	while (str[index] && str[index] != '"')
		index++;
	str = ft_substr(str, start, index - start);
	// new_token = create_token(NULL, ARG);
	// if (!new_token)
	// 	return (1);
	// append_token_list(head, new_token);
	printf("[ARG]%s\n", str);
	if (str[index] == '"')
	{
		printf("[SQUOTE]\n");
		// new_token = create_token(NULL, SQUOTE);
		// if (!new_token)
		// 	return (1);
		// append_token_list(head, new_token);
	}
	start = index;
	return (0);
}

