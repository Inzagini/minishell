#ifndef EXPANDER_H
# define EXPANDER_H

// # include "minishell.h"

typedef struct s_split
{
	char	*expanded;
	char	**split_tokens;
	int		count_token;
	t_token	*prev;
	t_token	*next;
	t_token	*last_added;
	t_token	*update;
	t_token	*new_token;
	int		merge_prev;
	int		merge_next;
}	t_split;

// expander.c
t_command	*expander(t_command *cmd_list, t_env *env);
void		check_builtins(t_command *cmd_list);

// expander_cmds.c
char		*find_path(char **envp);
char		*get_cmd(char **paths, char *cmd);
void		expand_commands(t_env *env, t_command *command);

// expander_env.c
t_env		*init_env(char **envp);
char		**copy_envp(char **envp, int exp);
int			copy_to_exp(char **copy, char **envp, int i, int j);
int			copy_to_env(char **copy, char **envp, int j);
void		clean_env(t_env *env);

// expander_args.c
char		*expand_argument(char *arg, char **env, char *result);
char		*append(char *result, char *to_add, size_t *len);
int			expand_arguments_dquote(t_env *env, t_command *cmd_list);
char		*find_var(char **env, char *var);

// expander_args_utils.c
int			is_valid_var_char(char c);
char		*ft_strndup(const char *src, size_t n);
size_t		ft_strspn(const char *str);
void		free_split(char **split_tokens);

// expander_merge.c
int			merge_arguments(t_command *cmd_list);
int			conduct_merge(t_token *arg, t_command *cmd, int *max);
int			calculate_size(t_token *token);

// expander_args_split.c
int			init_split(t_split *split,
				char **env, t_token **arg_list, t_token *arg);
void		update_arg_ids(t_split *split, t_token *arg);
int			expand_arguments_noquote(t_env *env, t_command *cmd_list);
int			handle_token_merge(t_split *split,
				t_token *arg, t_token **arg_list, int i);
int			split_argument(t_token **arg_list, t_token *arg,
				char **env, int arg_id);

// expander_args_split_utils.c
void		remove_token(t_token **arg_list, t_token *token);
void		insert_token_after(t_token **arg_list,
				t_token *after, t_token *new);
t_token		*create_token_split(char *content, int arg_id);
t_token		*find_previous_token(t_token *arg_list, t_token *token);
void		merge_tokens(t_token *first, t_token *second);

// expander_special.c
int			expand_tilde(t_env *env, t_command *cmd_list);
char		*replace_tilde(const char *content, char **env);
int			expand_special(t_env *env, t_command *cmd_list);
char		*replace_special(char *content, int status, char* find);

#endif
