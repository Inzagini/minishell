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

# include "libft.h"

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
}	t_env;

# include "tokenizer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "signals.h"

int	main_loop(t_token *head, char *input, t_command *cmd_list, t_env *env);

#endif
