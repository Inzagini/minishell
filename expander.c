#include "minishell.h"

/*
    - DONE get environment variables and save copy?
    - DONE get execution path + save in cmd_paths with split
    - DONE check command name and replace args[0]
    - DONE test with access stand_alone
    - DONE test with access and all available commands
    - DONE save working command in args[0] or input if none found
    - hanlde built-ins -> do nothing
    - check if $ found 
        -> if no brackets -> expand variable and replace (depending on SQuotes and DQuotes)
        -> if brackets -> command substitution process
    - check if ~ is found -> replace with home directory
*/

t_command   *expander(t_command *cmd_list, char **envp)
{
    t_env       env;
    t_command   *curr_cmd;
    char        *command;

    if (copy_envp(&env, envp) == 1)
        return (NULL);
    env.full_path = find_path(env.env_current);
    env.cmd_paths = ft_split(env.full_path, ':');
    if (!env.cmd_paths)
        return (NULL);
    curr_cmd = cmd_list;
    while (curr_cmd)
    {
        command = get_cmd(env.cmd_paths, curr_cmd->arguments[0]);
        if (command)
        {
            free (curr_cmd->arguments[0]);
            curr_cmd->arguments[0] = command;
        } 
        curr_cmd = curr_cmd->next;
    }
    return (NULL);
}

int    copy_envp(t_env *env, char **envp)
{
    int     i;
    int     j;
    char    **copy;

    i = 0;
    while (envp[i])
        i++;
    copy = malloc ((i + 1) * sizeof(char *));
    if (!copy)
        return (1);
    envp[i] = 0;
    j = -1;
    while (envp[++j])
    {
        copy[j] = ft_strdup(envp[j]);
        if (!copy[j])
        {
            while (--j >= 0)
                free (copy[j]);
            return (free (copy[i]), free (copy), 1);
        }
    }
    env->env_current = copy;
    return (0);
}

