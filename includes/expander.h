#include "minishell.h"

#ifndef EXPANDER_H
# define EXPANDER_H

typedef struct s_env
{ 
	char    **env_current;
    char    *full_path;
    char    **cmd_paths;
}	t_env;

t_command   *expander(t_command *cmd_list, char **envp);
int         copy_envp(t_env *env, char **envp);
void        check_builtins(t_command *cmd_list);


char    	*find_path(char **envp);
char    	*get_cmd(char **paths, char *cmd);
void	    expand_commands(t_env *env, t_command *command);

#endif
