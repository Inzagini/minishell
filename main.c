#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_token		*head;
	t_command	*cmd_list;
	t_env		*env;

	signal_setup();
	env = init_env(envp);
	while (1)
	{
		head = NULL;
		input = readline("Test prompt:");
		if (!input)
			break ;
		if (input[0])
		{
			add_history(input);
			if (tokenizer(input, &head))
			{
				clean_tokens(&head);
				free(input);
				continue;
			}
			print_tokens(head);
			cmd_list = parser(head);
			if (!cmd_list)
			{
				clean_tokens(&head);
				return 1;
			}
			clean_tokens(&head);
			expander(cmd_list, envp, env);
			executor(cmd_list, env);
			clean_commands(cmd_list);
		}
	}
	clean_env(env);
	rl_clear_history();
	return (0);
}
