/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:10:19 by asaadeh           #+#    #+#             */
/*   Updated: 2025/04/21 17:04:30 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/// global var

typedef struct s_cmd
{
	char			**cmd_line;
	char			*file_in;
	char			*file_out;
	int				append;
	char			*redirect;
	char			*pipe;
	char			*limiter;
	struct s_cmd	*next;
}	t_cmd;

typedef enum s_type
{
	TOKEN_PIPE,
	TOKEN_ARG,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	FILEIN,
	COMMAND,
	FILEOUT,
}					t_type;

typedef struct s_node
{
	char			*node;
	struct s_node	*next;
	t_type			cmd_type;
}					t_node;

typedef struct s_env
{
	char			*env_name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_minishell
{
	char			*name;
	char			**token_space;
	t_cmd			**cmd_list;
	t_node			*token_list;
	t_env			**env_list;
	char			**envps;
	int				last_exit;
}					t_minishell;


int					split_operation(t_minishell *shell, char operator);
t_node				*create_node_list(char **tokens);
void				append_node(t_node **head, t_node **current,
						t_node *new_node);
t_node				*create_new_node(char *token);

int					split(t_minishell *shell);
int					closed_quotes(t_minishell *shell, char qoute);
int					split_space(t_minishell *shell);
int					parsing(t_minishell **shell);
void				free_minishell(t_minishell *shell);
void				free_token_space(char **token_space);
t_minishell			*init_shell(t_minishell *shell, char **envp);
t_node				*fix_redirection(t_node *list);
int					put_type(t_minishell **shell);
void				free_and_exit(t_minishell *shell);
void				free_node(t_node *to_free);
void				process_node_list(t_minishell *shell);
void				define_cmd(t_minishell **shell);

void				free_tokens(t_node *list);

int					handle_quote(t_minishell *shell, char operator);
int					expand(t_minishell *shell);

char				*space_before_op(char *str, int i, int *len);
char				*space_after_op(char *str, int i, int *len);

char				*replace_spaces_inside_quotes(const char *input);
void				restore_spaces(char **tokens);

char				*handle_env(char *str, t_env *env_list);
char				*ft_trim_quotes(char *s1);
char				*ft_strjoin_free(char *s1, char *s2);
t_env				*create_env(char *env_var);
t_env				*copy_env_to_list(char **envp);
void				my_setenv(t_env **env_list, char *name, char *value);
char				*my_getenv(t_env *env_list, char *name);
int					handle_operation(t_minishell *shell);
int					handle_quotes_and_operators(t_minishell *shell);
int					has_operator_at_edges(char *str, int len);
int					has_invalid_repeated_operators(char *str);

int	fill_cmd(t_cmd *cmd2, t_node *temp);
void				init_cmd(t_cmd **cmd);
int				cmd_filling(t_minishell *shell);
void				set_cmd(t_cmd *cmd, char *file_name, char *var,
						t_type type);
void				handle_redirection(t_minishell **shell);
void				here_doc(t_cmd *cmd);
void				redirect_out(t_cmd *cmd);
void				redirect_in(t_cmd *cmd);
void				handle_export(char *str, t_env **env_list);
void				my_unsetenv(t_env **env_list, char *name);
void	free_env_list(t_env **env_list);
void	free_cmd_list(t_cmd **cmd_list);

void    get_path_cmd(t_minishell *shell, char **envp,char **args);
void    execute_cmd(char *cmd_path, t_minishell *shell, char **envp, char **cmd_line);
int		is_all_whitespace(const char *str);
int		ft_isspace(char c);


char	**copy_env_list_to_array(t_env *env_list);
int		get_env_list_size(t_env *env_list);
char	*join_env_pair(char *name, char *value);
void    is_builtin(t_minishell *shell, char **envp);
void ft_echo(t_minishell *shell, t_cmd *cmd);
int handle_echo_flag(char *arg);
void    ft_pwd();
void    ft_env(t_minishell *shell);
void    ft_export(t_minishell *shell, t_cmd *cmd);
void    sort_export_list_and_print(t_env **env_list);
void 	sort_list(t_env **env_list);
void    swap_nodes(t_env *a, t_env *b);

void    ft_unset(t_minishell *shell, t_cmd *cmd);
/// print functions
void				print_env_list(t_env **env_list);
void				prt_list(t_minishell **shell);
void				print(t_minishell **shell);

#endif