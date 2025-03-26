/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishill.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:10:19 by asaadeh           #+#    #+#             */
/*   Updated: 2025/03/26 13:50:31 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <string.h>


/// global var

typedef enum s_type
{
    TOKEN_PIPE, // | 0
	TOKEN_ARG, // CMD, ARG 1
	TOKEN_REDIRECT_IN, // < 2
	TOKEN_REDIRECT_OUT, // > 3
	TOKEN_APPEND, // >> 4
	TOKEN_HEREDOC, // << 5
    FILEIN, // 6
    COMMAND, // 7
    FILEOUT, // 8
}   t_type;

typedef struct s_node
{
    char *node;
    struct s_node *next;
    t_type      cmd_type;
} t_node;

typedef struct s_minishell
{
    char *name;
    char **token_space;
    t_node *token_list;
}   t_minishell;

typedef struct  s_env
{
    char    *env_name;
    char    *value;
    struct  s_env   *next;
}   t_env;

int split_operation(t_minishell *shell, char operator);
t_node *create_node_list(char **tokens);
int split(t_minishell *shell);
int closed_quotes(t_minishell *shell, char qoute);
int split_space(t_minishell *shell);
int    parsing(t_minishell **shell);
void    print(t_minishell **shell);
void free_minishell(t_minishell *shell);
void free_token_space(char **token_space);
t_minishell *init_shell(t_minishell *shell);
t_node  *fix_redirection(t_node *list);
int    put_type(t_minishell **shell);
t_node  *fix_redirection(t_node *list);
void    prt_list(t_minishell **shell);
void free_and_exit(t_minishell *shell);
void free_node(t_node *to_free);
void process_node_list(t_minishell *shell);

void    define_cmd(t_minishell **shell);

void    free_tokens(t_node *list);

int	handle_quote(t_minishell *shell, char operator);

void    expand(t_minishell *shell);

char    *handle_env(char *str, t_env *env_list);
char    *ft_trim_quotes(char *s1);
char    *ft_strjoin_free(char *s1, char *s2);
t_env   *create_env(char *env_var);
t_env   *copy_env_to_list();
void    my_setenv(t_env **env_list, char *name, char *value, int overwrite);
char    *my_getenv(t_env *env_list, char *name);

void print_env_list(t_env *env_list);
#endif