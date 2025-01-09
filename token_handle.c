#include "minishell.h"

int	sep_handle(char *str, int *index, t_token **head)
{
	t_token	*new_token;

	printf("[SEP]\n");
	new_token = create_token(NULL, SEP);
	if (!new_token)
		return (1);
	append_token_lst(head, new_token);
	while (str[(*index)] == ' ')
		(*index)++;
	return (0);
}

int	pipe_handle(char *str, int *index, t_token **head)
{
	t_token	*new_token;

	printf("[PIPE]\n");
	new_token = create_token(NULL, PIPE);
	if (!new_token)
		return (1);
	append_token_lst(head, new_token);
	return (0);
}

int	squote_handle(char *str, int *index, t_token **head)
{
	t_token	*token;
	int		start;
	char	*sub_str;

	printf("[SQUOTES]\n");
	token = create_token(NULL, SQUOTE);
	append_token_lst(head, token);
	start = ++(*index);
	while (str[(*index)] && str[(*index)] != '\'')
		(*index)++;
	sub_str = ft_substr(str, start, (*index) - start);
	token = create_token(sub_str, ARG);
	append_token_lst(head, token);
	printf("[ARG]%s\n", sub_str);
	if (str[(*index)] == '\'')
	{
		printf("[SQUOTES]\n");
		token = create_token(NULL, SQUOTE);
		append_token_lst(head, token);
	}
	return (0);
}

int	arg_handle(char *input_str, int start, int index, t_token **head)
{
	t_token	*new_token;
	char	*str;

	str = ft_substr(input_str, start, index + 1 - start);
	if (!str)
		return (1);
	printf("[ARG]%s\n", str);
	new_token = create_token(str, ARG);
	if (!new_token)
		return (free(str), 1);
	append_token_lst(head, new_token);
	return (0);
}

int	cmd_handle(char *input_str, int start, int index, t_token **head)
{
	t_token	*new_token;
	char	*str;

	str = ft_substr(input_str, start, index + 1 - start);
	if (!str)
		return (1);
	printf("[CMD]%s\n", str);
	new_token = create_token(str, CMD);
	if (!new_token)
		return (free(str), 1);
	append_token_lst(head, new_token);
	return (0);
}
