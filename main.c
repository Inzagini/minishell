#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_token		*head;
	t_command	*cmd_list;
	t_env		*env;

	(void)argc;
	(void)argv;
	cmd_list = NULL;
	head = NULL;
	input = NULL;
	signal_setup();
	env = init_env(envp);
	while (main_loop(head, input, cmd_list, env))
		continue ;
	clean_env(env);
	rl_clear_history();
	return (0);
}

int	main_loop(t_token *head, char *input, t_command *cmd_list, t_env *env)
{
	head = NULL;
	export_to_env(env->shell_var, env);
	export_to_exp(env->shell_var, env);
	if (input)
		free (input);
	input = readline("BROKEN_SHELL: ");
	if (!input)
		return (0);
	if (input[0])
	{
		add_history(input);
		if (tokenizer(input, &head, env))
			return (clean_tokens(&head), free(input), 1);
		cmd_list = parser(head, env);
		if (!cmd_list)
		{
			clean_tokens(&head);
			return (1);
		}
		clean_tokens(&head);
		expander(cmd_list, env);
		executor(cmd_list, env);
		clean_commands(cmd_list);
	}
	return (1);
}
