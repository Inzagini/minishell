#include "minishell.h"

void	test_signal(int sig)
{
	(void)sig;
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_token		*head;
	t_command	*cmd_list;
	t_env		*env;

	// signal(SIGINT, test_signal);

	env = init_env(envp);
	while (1)
	{
		head = NULL;
		input = readline("1 | Test prompt:");
		if (input[0])
            add_history(input);
        // input = " ";
		tokenizer(input, &head);
        free (input);
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
    rl_clear_history();
	return (0);
}

