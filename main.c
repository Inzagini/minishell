#include "minishell.h"

int	main(void)
{
	char	*test;
	t_token	*head;
	t_command *cmd_list;

	head = NULL;
	test = readline("Test prompt:");
	printf("%s\n", test);
	tokenizer(test, &head);
	// cmd_list = parser(head);

	// // Print the commands
    // t_command *temp = cmdt_list;
    // while (temp)
    // {
    //     print_command(temp);
    //     temp = temp->next;
    // }
    // // Free memory
    // free_commands(cmd_list);
	// free_tokens(head);
    return 0;
}
