#include "minishell.h"

// To properly handle cases like $HOME'$ABC',
// your parser needs to accommodate multiple tokens being
// combined into a single argument, while also preserving the quotation
// context for each individual token. This ensures that the expander c
// an accurately decide which parts of the argument to expand and which to treat as literal.

void	test_signal(int sig)
{
	(void)sig;
}

int	main(int argc, char **argv, char **envp)
{
	char		*test;
	t_token		*head;
	t_command	*cmd_list;
	t_env		*env;

	// signal(SIGINT, test_signal);

	env = init_env(envp);
	while (1)
	{
		head = NULL;
		test = readline("1 | Test prompt:");
		// test = " ";
		tokenizer(test, &head);
		cmd_list = parser(head);
		if (!cmd_list)
		{
			clean_tokens(&head);
			return 1;
		}
		clean_tokens(&head);
		expander(cmd_list, envp, env);
		// t_command *temp = cmd_list;
		// while (cmd_list)
		// {
		//     print_command(cmd_list);
		//     cmd_list = cmd_list->next;
		// }
		// cmd_list = temp;
		executor(cmd_list, env);
		//// Free memory
		clean_commands(cmd_list);
	}
	clean_env(env);
	return (0);
}

