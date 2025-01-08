#include "minishell.h"

int	sep_handle(char *str, int index, t_token **head)
{
	t_token	*new_token;
	char*	content;

	if (str[index] != ' ')
		return (1);
	printf("[SEP]\n");
	content = ft_substr((const char) str, (unsigned int) index, 1);
	if (!content)
		return (1);
	new_token = create_token(content);
	if (!new_token)
		return (1);
	append_token_list(head, new_token);
	return (0);
}
