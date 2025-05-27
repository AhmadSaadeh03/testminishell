/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:04:30 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/27 14:03:47 by fghanem          ###   ########.fr       */
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
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>

extern volatile sig_atomic_t	g_signal;

typedef struct s_here
{
	char						*limt;
	char						*content;
	struct s_here				*next;
}								t_here;

typedef struct s_pipes
{
	int							cmd_count;
	int							*pipe_fd;
	int							prev_fd;
	pid_t						*pid;
}								t_pipes;

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
}								t_type;

typedef struct s_redirect
{
	char						*file_name;
	t_type						type;
	struct s_redirect			*next;
}								t_redirect;

typedef struct s_cmd
{
	char						**cmd_line;
	int							heredoc_flag;
	int							redir_flag;
	t_redirect					*redirect;
	t_here						*heredocs;
	t_pipes						pipes;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_node
{
	char						*node;
	struct s_node				*next;
	t_type						cmd_type;
}								t_node;

typedef struct s_env
{
	char						*env_name;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef struct s_minishell
{
	char						*name;
	char						**token_space;
	t_cmd						**cmd_list;
	t_node						*token_list;
	t_env						**env_list;
	char						**envps;
	int							last_exit;
}								t_minishell;

char	*space_before_op(char *str, int i, int *len);
char	*space_after_op(char *str, int i, int *len);
char	*add_cmd(char *token);
char	*find_path(char **path, char *cmd);
char	*replace_spaces_inside_quotes(char *input);
char	*read_input(char *limiter, t_minishell *shell);
char	*my_getenv(t_env *env_list, char *name);
char	**copy_env_list_to_array(t_env *env_list);
char	*join_env_pair(char *name, char *value);
char	*handle_env(char *str, t_env *env_list);
char	*ft_trim_quotes(char *s1);
char	**get_path_array(t_minishell *shell, char *arg);
char	*ft_strjoin_free(char *s1, char *s2);
char	*remove_all_spaces(char *str);


int		is_valid_number_format(char *arg,
			int *sign,
			long *number);
int		is_all_whitespace(char *str);
int		ft_isspace(char c);
int		get_env_list_size(t_env *env_list);
int		handle_echo_flag(char *arg);
int		check_digit(char *arg);

int		cmd_count(t_cmd *cmd);
int		handle_operation(t_minishell *shell);
int		is_builtin(char *cmd);
int		check_cmd_path(t_minishell *shell,
			char **cmd_line);
int		split_operation(t_minishell *shell,
			char operator);
int		split(t_minishell *shell);
int		cmd_filling(t_minishell *shell);
int		handle_redirection(t_cmd *cmd,
			t_minishell *shell);
int		redirect_out(char *file_name, t_type type);
int		redirect_in(char *file_name);
int		closed_quotes(t_minishell *shell, char qoute);
int		split_space(t_minishell *shell);
int		parsing(t_minishell **shell);
int		expand(t_minishell *shell);
int		put_type(t_minishell **shell);
int		handle_quotes_and_operators(t_minishell *shell);
int		prepare_env_and_check(t_minishell *shell,
			char *cmd_path, char *arg);
int		has_operator_at_edges(char *str, int len);
int		has_invalid_repeated_operators(char *str);
int		fill_cmd(t_cmd *cmd2, t_node *temp);
int		alloc_pipe_resources(t_pipes *p, int count);
int		init_pipe_data(t_pipes *p, int count);
int		create_child_processes(t_minishell *shell, t_pipes *pipe_data,
			t_cmd *cmd);

void	my_setenv(t_env **env_list, char *name, char *value);
void	add_redirect(t_cmd *cmd, char *file_name, t_type type);
void	handle_export(char *str, t_env **env_list);
void	append_node(t_node **head, t_node **current, t_node *new_node);
void	free_array(char **array);
void	add_redirect(t_cmd *cmd, char *file_name, t_type type);
void	free_node(t_node *to_free);
void	process_node_list(t_minishell *shell);
void	free_tokens(t_node *list);
void	my_unsetenv(t_env **env_list, char *name);
void	free_env_list(t_env *head);
void	get_path_cmd(t_minishell *shell, char **args);
void	restore_spaces(char **tokens);
void	execute_cmd(char *cmd_path, t_minishell *shell,
			char **envp, char **cmd_line);
void	exec_builtin(t_minishell *shell, char **cmd_line);
void	ft_echo(t_minishell *shell, char **cmd_line, int newline);
void	ft_pwd(void);
void	ft_env(t_minishell *shell);
void	ft_export(t_minishell *shell, char **cmd_line);
void	sort_export_list_and_print(t_env **env_list);
void	sort_list(t_env **env_list);
void	swap_nodes(t_env *a, t_env *b);
void	ft_exit(t_minishell *shell, char **cmd_line);
void	ft_cd(t_minishell *shell, char **cmd_line);
void	ft_unset(t_minishell *shell, char **cmd_line);
void	free_here_list(t_here *heredocs);
void	add_heredoc(t_cmd *cmd, char *limit);
void	exec_heredoc(t_cmd *cmd, t_minishell *shell);
void	free_cmd(t_cmd *cmd);
void	execute_one_cmd(t_minishell *shell, t_cmd *cmd);
void	free_redir_list(t_redirect *redir);
void	external_cmd(t_minishell *shell, t_cmd *cmd);
void	exec_red_cmd(t_cmd *cmd, t_minishell *shell,
			int fl);
void	exec_red_only(t_cmd *cmd, t_minishell *shell);
void	exec_pipe(t_minishell *shell);
void	executing(t_minishell *shell);
void	close_fd(t_pipes *pipe_data);
void	free_exit(t_minishell *shell);
void	preprocess_heredocs(t_cmd *cmd,
			t_minishell *shell);
void	heredoc_child(t_cmd *cmd, t_minishell *shell);
void	free_pipe_data(t_pipes *pipe_data);
void	wait_all_children(t_pipes *pipe_data,
			t_minishell *shell);
void	handle_child_process(t_minishell *shell, t_cmd *cmd,
			t_pipes *pipe_data, int i);
void	free_minishell(t_minishell *shell);
void	print_env_list(t_env **env_list);
void	handle_invalid_arg(int check_f, t_minishell *shell);
void	handle_signals(int mode);
void	print_error(char *mess, char *type);
void	print_echo_args(char *arg, int status, int space_flag);
void	child_process(t_cmd *cmd, t_minishell *shell, int flag);
void	handle_exit_status(t_minishell *shell, int status);
void	herdoc_signals(int signal_number);
void	handle_after_child(int signal_number);
void	handle_ctrl_c_on_process(int signal_number);
void	handle_ctrl_c(int signal_number);

t_minishell	*init_shell(char **envp);
t_node	*create_node_list(char **tokens);
t_node	*create_new_node(char *token);
t_node	*fix_redirection(t_node *list);
t_env	*create_env(char *env_var);
t_env	*copy_env_to_list(char **envp);
t_cmd	*init_cmd(void);
t_here	*creat_heredoc(char *limit);

#endif
