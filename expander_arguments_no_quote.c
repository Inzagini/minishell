#include "minishell.h"
#include <string.h>

int expand_and_split_argument_noquote(t_token **arg_list, t_token *arg, char **env, int *next_arg_id)
{
    char *expanded = expand_argument_dquote(arg->content, env); // Use expand_argument_noquote
    if (!expanded)
        return (1);

    char **split_tokens = ft_split(expanded, ' '); // Split by whitespace
    free(expanded);
    if (!split_tokens)
        return (1);

    t_token *prev = find_previous_token(*arg_list, arg);
    t_token *next = arg->next;

    t_token *last_added = NULL; // Track the last token added for proper insertion
    for (int i = 0; split_tokens[i]; i++)
    {
        t_token *new_token = create_token2(split_tokens[i], (*next_arg_id)++);
        if (!new_token)
        {
            free_split(split_tokens);
            return (1);
        }

        // If we're at the first split token, merge with the previous token
        if (i == 0 && prev)
        {
            merge_tokens(prev, new_token);
            last_added = prev; // Update the last added token to prev
        }
        // If we're at the last token, merge with the next token
        else if (!split_tokens[i + 1] && next)
        {
            merge_tokens(new_token, next);
        }
        // Otherwise, insert as a new token in the list
        else
        {
            if (last_added)
                insert_token_after(arg_list, last_added, new_token);
            else
                insert_token_after(arg_list, arg, new_token); // Insert after the original token
            last_added = new_token; // Update last added token to new_token
        }
    }

    free_split(split_tokens); // Free the split tokens array
    remove_token(arg_list, arg); // Remove the original token

    return (0);
}



int expand_arguments_noquote(t_env *env, t_command *cmd_list)
{
    int next_arg_id = 1; // Start from 1 for arguments (assuming cmd starts with 0)
    t_token *arg;

    while (cmd_list)
    {
        arg = cmd_list->arg_tokens;
        while (arg)
        {
            if (arg->quote_identifier == 0 && ft_strchr(arg->content, '$') != NULL) // Unquoted
            {
                if (expand_and_split_argument_noquote(&cmd_list->arg_tokens, arg, env->env_current, &next_arg_id))
                    return (1);
            }
            arg = arg->next;
        }
        cmd_list = cmd_list->next;
    }
    return (0);
}

void free_split(char **split_tokens)
{
    if (!split_tokens)
        return;
    for (int i = 0; split_tokens[i]; i++)
        free(split_tokens[i]);
    free(split_tokens);
}

void remove_token(t_token **arg_list, t_token *token)
{
    if (!arg_list || !*arg_list || !token)
        return;

    if (*arg_list == token)
    {
        *arg_list = token->next;
    }
    else
    {
        t_token *prev = *arg_list;
        while (prev && prev->next != token)
            prev = prev->next;

        if (prev)
            prev->next = token->next;
    }

    free(token->content); // Free the token content
    free(token);          // Free the token itself
}

void insert_token_after(t_token **arg_list, t_token *after, t_token *new_token)
{
    if (!new_token)
        return;

    if (!after) // Insert at the head of the list
    {
        new_token->next = *arg_list;
        *arg_list = new_token;
    }
    else
    {
        new_token->next = after->next;
        after->next = new_token;
    }
}

t_token *create_token2(char *content, int arg_id)
{
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return (NULL);

    new_token->content = ft_strdup(content); // Duplicate the content
    if (!new_token->content)
    {
        free(new_token);
        return (NULL);
    }
    new_token->arg_group_id = arg_id;
    new_token->quote_identifier = 0; // Default to unquoted
    new_token->next = NULL;          // Initialize the next pointer to NULL
    return (new_token);
}

t_token *find_previous_token(t_token *arg_list, t_token *token)
{
    if (!arg_list || !token || arg_list == token)
        return (NULL);

    t_token *current = arg_list;
    while (current && current->next != token)
        current = current->next;

    return (current);
}

void merge_tokens(t_token *first, t_token *second)
{
    if (!first || !second)
        return;

    size_t new_len = ft_strlen(first->content) + ft_strlen(second->content) + 1;
    char *merged_content = malloc(new_len);
    if (!merged_content)
        return;

    strcpy(merged_content, first->content);
    strcat(merged_content, second->content);

    free(first->content);
    first->content = merged_content;
    first->next = second->next;
    free(second->content);
    free(second);
}


