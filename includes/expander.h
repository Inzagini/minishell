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

int         expand_arguments_dquote(t_env *env, t_command *cmd_list);
char        *expand_argument_dquote(char *arg, char **env);
char        *find_var(char **env, char *var);
int         is_valid_var_char(char c);
char	    *find_var(char **envp, char *var);
char        *ft_strndup(const char *src, size_t n);
size_t      ft_strspn(const char *str, const char *accept);
char	*append_to_result(char *result, char *to_add, size_t *len);


int			merge_arguments(t_command *cmd_list);
int			calculate_size(t_token *token);

int         expand_arguments_noquote(t_env *env, t_command *cmd_list);
int         expand_and_split_argument_noquote(t_token **arg_list, t_token *arg, char **env, int *next_arg_id);
char        *expand_argument_noquote(char *arg, char **env);

void free_split(char **split_tokens);
void remove_token(t_token **arg_list, t_token *token);
void insert_token_after(t_token **arg_list, t_token *after, t_token *new_token);
t_token *create_token2(char *content, int arg_id);
t_token *find_previous_token(t_token *arg_list, t_token *token);
void merge_tokens(t_token *first, t_token *second);





















#endif
