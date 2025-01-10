#include "minishell.h"

int	main(void)
{
	char	*test;
	t_token	*head;
	t_command *cmd_list;

	head = NULL;
//	test = readline("Test prompt:");
	test = "grep 123 | ls '-l' <abc";
	tokenizer(test, &head);
	cmd_list = parser(head);
	if (!cmd_list)
	{
		free_tokens(head);
		return 1;
	}
	// Print the commands
    t_command *temp = cmd_list;
    while (temp)
    {
        print_command(temp);
        temp = temp->next;
    }
    // Free memory
    clean_commands(cmd_list);
	free_tokens(head);
    return 0;
}
