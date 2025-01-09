#include "minishell.h"

t_token	*tokenizer(char *input_str, t_token **head);
int	meta_char(char *str, int *index, t_token **head);
void	print_lst(t_token *lst);


t_token	*tokenizer(char *input_str, t_token **head)
{
	t_data	data;
	t_token	*token;

	data.index = -1;
	data.start = 0;
	data.cmd_flag = 0;
	while (input_str[++(data.index)])
	{
		if (input_str[data.index] == ' ')
			sep_handle(&data, head);
		if (input_str[data.index] == '\'')
			squote_handle(input_str, &data, head);
		else if (input_str[data.index] == '"')
			dquote_handle(input_str, &data, head);
		else if (input_str[data.index] == '|')
			pipe_handle( &data, head);
		else if (input_str[data.index + 1] == ' ' || input_str[data.index + 1] == 0)
		{
			if (data.cmd_flag == 0)
				cmd_handle(input_str, &data, head);
			else
				arg_handle(input_str, &data, head);
		}
	}
	return (NULL);
}

// int	meta_char(char *str, int *index, t_token **head)
// {
// 	if (str[(*index)] == ' ')
// 		sep_handle(str, index, head);
// 	if (str[(*index)] == '|')
// 		pipe_handle(str, index, head);
// 	else if (str[(*index)] == '\'')
// 		squote_handle(str, index, head);
// 	else
// 		return (1);
// 	return (0);
// }

t_token	*create_token(char *content, t_token_type token_type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = token_type;
	new_token->content = content;
	new_token->previous = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	append_token_lst(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
	new_token->previous = tmp;
}

void	print_lst(t_token *lst)
{
	if (!lst)
	{
		printf("empty list\n");
		return ;
	}
	while (lst)
	{
		printf("token type: %d\tcontent %s\n", lst->type, lst->content);
		lst = lst->next;
	}
}
