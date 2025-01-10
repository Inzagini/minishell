#include "minishell.h"

int	main(int argc, char **argv)
{
	char		*test;
	t_token		*head;
	// t_command	*cmd_list;

	head = NULL;
	// test = readline("Test prompt:");
	test = argv[1];
	argc = 0;
	if (!tokenizer(test, &head))
		printf("Token error\n");
	token_cleaner(head);
	// cmd_list = parser(head);

	// // Print the commands
    // t_command *temp = cmd_list;
    // while (temp)
    // {
    //     print_command(temp);
    //     temp = temp->next;
    // }
    // // Free memory
    // free_commands(cmd_list);
	// free_tokens(head);
    // return 0;
}
