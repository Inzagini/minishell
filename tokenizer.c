#include "minishell.h"

t_token	*tokenizer(char *input_str, t_token *head);

int	main(void)
{
	char	*test;
	t_token	*head;
	test = readline("Test prompt:");
	printf("%s\n", test);
	tokenizer(test, head);
}

t_token	*tokenizer(char *input_str, t_token *head)
{
	int	index;
	int	start;
	int	cmd_flag;
	char	*str;
	t_token	*token;

	index = -1;
	start = 0;
	cmd_flag = 0;
	while (input_str[++index])
	{
		if (sep_handle(input_str, index, head) == 0)
		{
			start = index;
		}
		else if (input_str[index] == '|')
		{
			printf("[PIPE]\n");
			start = index;
			cmd_flag = 0;
		}
		else if (input_str[index] == '"')
		{
			printf("[DQUOTES]\n");
			start = ++index;
			while (input_str[index] && input_str[index] != '"')
				index++;
			str = ft_substr(input_str, start, index - start);
			printf("[ARG]%s\n", str);
			if (input_str[index] == '"')
				printf("[DQUOTES]\n");
			free(str);
			start = index;
		}
		else if (input_str[index + 1] == ' ' || input_str[index + 1] == 0)
		{
			str = ft_substr(input_str, start, index + 1 - start);
			if (cmd_flag == 0)
				printf("[CMD]%s\n", str);
			else
				printf("[ARG]%s\n", str);
			free(str);
			start = index;
			cmd_flag = 1;
			// token = create_token(str);
			// append_token(head, token);
		}
	}
	return (NULL);
}


t_token	*create_token(char *content)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = get_token_type();
	new_token->content = content;
	new_token->previous = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	append_token_list(t_token **head, t_token *new_token)
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
