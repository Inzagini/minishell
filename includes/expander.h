#include "minishell.h"

#ifndef EXPANDER_H
# define EXPANDER_H

typedef struct s_env
{
	char	**env_current;
	char	**export_current;
	char	*full_path;
	char	**cmd_paths;
	int		last_exit_status;
}	t_env;

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

t_command	*expander(t_command *cmd_list, char **envp, t_env *env);
void		check_builtins(t_command *cmd_list);


char		*find_path(char **envp);
char		*get_cmd(char **paths, char *cmd);
void		expand_commands(t_env *env, t_command *command);

void		clean_env(t_env *env);
char		**copy_envp(char **envp);
t_env		init_env();

int			expand_arguments_dquote(t_env *env, t_command *cmd_list);
char		*expand_argument(char *arg, char **env);
char		*find_var(char **env, char *var);
int			is_valid_var_char(char c);
char		*find_var(char **envp, char *var);
char		*ft_strndup(const char *src, size_t n);
size_t		ft_strspn(const char *str);
char		*append_to_result(char *result, char *to_add, size_t *len);

int			merge_arguments(t_command *cmd_list);
int			calculate_size(t_token *token);

int			init_split(t_split *split, char **env, t_token **arg_list, t_token *arg);
void		update_arg_ids(t_split *split, t_token *arg);

int			expand_arguments_noquote(t_env *env, t_command *cmd_list);
int			split_argument(t_token **arg_list, t_token *arg, char **env, int arg_id);
char		*expand_argument_noquote(char *arg, char **env);

void		free_split(char **split_tokens);
void		remove_token(t_token **arg_list, t_token *token);
void		insert_token_after(t_token **arg_list, t_token *after, t_token *new_token);
t_token		*create_token_split(char *content, int arg_id);
t_token		*find_previous_token(t_token *arg_list, t_token *token);
void		merge_tokens(t_token *first, t_token *second);

int			expand_tilde(t_env *env, t_command *cmd_list);
char		*replace_tilde(const char *content, char **env);
























#endif
