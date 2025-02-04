/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:41:48 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 15:10:41 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <stdint.h>
# include "libft.h"

# include "tokenizer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "signals.h"

typedef struct s_env
{
	char	**env;
	char	**exp;
	char	*full_path;
	char	**cmd_paths;
	int		last_exit_status;
	char	*shell_name;
	char	*shell_var;
	pid_t	child_pid;
	pid_t	prev_pid;
}	t_env;

int	main_loop(t_token *head, char *input, t_command *cmd_list, t_env *env);

void print_command(t_command *cmd);


#endif
