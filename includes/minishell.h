
#ifndef MINISHELL_H
# define MINISHELL_H

#define _GNU_SOURCE // check what this actually is https://42born2code.slack.com/archives/C04C5N7EWS2/p1686320400227179?thread_ts=1686310183.263039&cid=C04C5N7EWS2

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include "tokenizer.h"
# include "parser.h"
# include "executor.h"
# include "expander.h"

#endif
