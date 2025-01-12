#include "minishell.h"

// if the VAR cannot be found, it expands to 0
// can rely on the identified quotes
// if in double quotes -> expands into single argument (no word splitting)
// if in single quotes -> expands into multiple arguments (word splitting)

int expand_arguments(t_env *env, t_command *cmd_list)
{
    while (cmd_list)
    {
        




        cmd_list = cmd_list->next;
    }
    return (0);
}

int identify_env_var(char *arg)
{
    char    *env_start;
    
    env_start = ft_strchr(arg, '$');
    return (0);




}