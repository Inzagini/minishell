#include "minishell.h"

int	main(int argc, char **argv)
{
	char		*test;
	t_token		*head;
	t_command	*cmd_list;

	head = NULL;
	// test = readline("Test prompt:");
	test = "< file grep 123 > test | ls -l | abcd <<t";
	tokenizer(test, &head);
	cmd_list = parser(head);
	if (!cmd_list)
	{
		token_cleaner(head);
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
	token_cleaner(head);
    return 0;
}
