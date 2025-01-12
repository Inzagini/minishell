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

    if (copy_envp(&env, envp) == 1)
        return (NULL);
    env.full_path = find_path(env.env_current);
    env.cmd_paths = ft_split(env.full_path, ':');
    if (!env.cmd_paths)
        return (NULL);
    check_builtins(cmd_list);
    expand_commands(&env, cmd_list);

    return (NULL);
}

void    check_builtins(t_command *cmd_list)
{
    while (cmd_list)
    {
        char    *arg;
        size_t  len;

        arg = cmd_list->arguments[0];
        if (ft_strncmp(arg, "echo", len) == 0)
            cmd_list->builtin_flag = 1;
        if (ft_strncmp(arg, "cd", len) == 0)
            cmd_list->builtin_flag = 1;
        if (ft_strncmp(arg, "pwd", len) == 0)
            cmd_list->builtin_flag = 1;
        if (ft_strncmp(arg, "export", len) == 0)
            cmd_list->builtin_flag = 1;
        if (ft_strncmp(arg, "unset", len) == 0)
            cmd_list->builtin_flag = 1;
        if (ft_strncmp(arg, "env", len) == 0)
            cmd_list->builtin_flag = 1;
        if (ft_strncmp(arg, "exit", len) == 0)
            cmd_list->builtin_flag = 1;
        cmd_list = cmd_list->next;
    }
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

