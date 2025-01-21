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

# include "tokenizer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "signals.h"

#endif
