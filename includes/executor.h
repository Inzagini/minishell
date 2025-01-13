#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>


int	executor(t_command *lst_cmd);

int	lst_len(t_command *lst);

#endif
