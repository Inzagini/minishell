#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*test;
	t_token		*head;
	t_command	*cmd_list;
    t_env       env;

	head = NULL;
	// test = readline("Test prompt:");
	test = "grep 123 > testfile | < test /usr/bin/grep SHELLSHELL << abc";
	tokenizer(test, &head);
	cmd_list = parser(head);
	if (!cmd_list)
	{
		token_cleaner(head);
		return 1;
	}
	// Print the commands
    env = init_env();
    expander(cmd_list, envp, &env);
	t_command *temp = cmd_list;
    while (temp)
    {
        print_command(temp);
        temp = temp->next;
    }
    
	// Free memory
    clean_env(&env);
    clean_commands(cmd_list);
	token_cleaner(head);
    return 0;
}

