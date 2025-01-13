#include "minishell.h"

// To properly handle cases like $HOME'$ABC',
// your parser needs to accommodate multiple tokens being
// combined into a single argument, while also preserving the quotation
// context for each individual token. This ensures that the expander c
// an accurately decide which parts of the argument to expand and which to treat as literal.

int	main(int argc, char **argv, char **envp)
{
	char		*test;
	t_token		*head;
	t_command	*cmd_list;
    t_env       env;

	head = NULL;
	// test = readline("Test prompt:");
	test = "grep abc'$USER'  | ls -l | cat -e ";
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

	// executor(cmd_list);

	// Free memory
    // clean_env(&env);
    // clean_commands(cmd_list);
	// token_cleaner(head);
    return 0;
}

