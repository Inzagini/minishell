#include "minishell.h"

#ifndef EXPANDER_H
# define EXPANDER_H

typedef struct s_env
{ 
	char    **env_current;
    char    *full_path;
    char    **cmd_paths;
}	t_env;

t_command   *expander(t_command *cmd_list, char **envp, t_env *env);
void        check_builtins(t_command *cmd_list);


char        *find_path(char **envp);
char        *get_cmd(char **paths, char *cmd);
void        expand_commands(t_env *env, t_command *command);

void        clean_env(t_env *env);
int         copy_envp(t_env *env, char **envp);
t_env       init_env();

int         expand_arguments(t_env *env, t_command *cmd_list);
char        *expand_argument(char *arg, char **env);
char        *find_var(char **env, char *var);
int         is_valid_var_char(char c);
char	    *find_var(char **envp, char *var);
char        *ft_strndup(const char *src, size_t n);
size_t      ft_strspn(const char *str, const char *accept);






#endif
