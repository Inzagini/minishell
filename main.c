/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quannguy <quannguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:43:46 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/06 14:37:37 by quannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	export_to_env(env->shell_var, env);
	export_to_exp(env->shell_var, env);
	while (main_loop(head, input, cmd_list, env))
		continue ;
	clean_env(env);
	rl_clear_history();
	return (0);
}

int	main_loop(t_token *head, char *input, t_command *cmd_list, t_env *env)
{
	head = NULL;
	input = readline("BROKEN_SHELL: ");
	if (g_sigint == 1)
	{
		env->last_exit_status = 130;
		g_sigint = 0;
	}
	if (!input)
		return (write(1, "exit\n", 5), 0);
	if (input[0])
	{
		add_history(input);
		if (tokenizer(input, &head, env))
			return (1);
		cmd_list = parser(head, env);
		if (!cmd_list)
			return (clean_tokens(&head), 1);
		clean_tokens(&head);
		expander(cmd_list, env);
		executor(cmd_list, env);
		clean_commands(cmd_list);
	}
	return (1);
}
