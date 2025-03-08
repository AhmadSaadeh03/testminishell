/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishill.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:10:19 by asaadeh           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/01 15:45:20 by asaadeh          ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2025/03/03 15:31:17 by fghanem          ###   ########.fr       */
=======
/*   Updated: 2025/03/08 14:25:06 by fghanem          ###   ########.fr       */
>>>>>>> f26bb66 (new)
>>>>>>> 5213311 (new)
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>
<<<<<<< HEAD
=======

typedef enum s_type
{
    TOKEN_PIPE, // | 0
	TOKEN_WORD, // CMD, ARG 1
	TOKEN_REDIRECT_IN, // < 2
	TOKEN_REDIRECT_OUT, // > 3
	TOKEN_APPEND, // >> 4
	TOKEN_HEREDOC, // << 5
<<<<<<< HEAD
    // FILEIN, // 6
    // COMMAND, // 7
    // FILEOUT, // 8
=======
    FILEIN, // 6
    COMMAND, // 7
    FILEOUT, // 8
>>>>>>> f26bb66 (new)
    
}   t_type;

typedef struct s_cmd
{
    char    **args;
    char    *file_in;
    char    *file_out;
    struct s_cmd    *next;
}   t_cmd;

>>>>>>> 5213311 (new)
typedef struct s_node
{
    char *node;
    struct s_node *next;
} t_node;
typedef struct s_token
{
    char pipe;
    char *append; // >>
    char redirect_out; //>
    char redirect_in; //<
    char  *quoted;
}t_tokentype;

typedef struct s_minishell
{
<<<<<<< HEAD
        char *name;
        char **token_space;
        t_node *token_list;
        t_tokentype *token_type;
<<<<<<< HEAD
}t_minishell;
=======
        t_cmd       **cmd_list;
=======
    char *name;
    char **token_space;
    t_node *token_list;
    t_tokentype *token_type;
    t_cmd       **cmd_list;
>>>>>>> f26bb66 (new)
}   t_minishell;
>>>>>>> 5213311 (new)

int split_operation(t_minishell *shell, char operator);
t_node *create_node_list(char **tokens);
int split(t_minishell *shell);
int closed_quotes(t_minishell *shell, char qoute);
//void split_quotes(t_minishell *shell, char operator);
int split_space(t_minishell *shell);
<<<<<<< HEAD
int init_operation(t_minishell *shell);
<<<<<<< HEAD
int qoutes_handling(t_minishell *shell,char qoute);
=======
=======
// int init_operation(t_minishell *shell);
>>>>>>> f26bb66 (new)
int qoutes_handling(t_minishell *shell,char qoute);

void    parsing(t_minishell **shell);
void    init_cmd(t_cmd **cmd);
<<<<<<< HEAD
// void    print(t_minishell **shell);
void    print(t_minishell **shell);
=======
void    print(t_minishell **shell);

void free_minishell(t_minishell *shell);
void free_token_space(char **token_space);
void free_cmd(t_cmd **cmd);
t_minishell *init_shell(t_minishell *shell);
int init_token(t_tokentype *token);

t_node  *fix_redirection(t_node *list);

void    put_type(t_minishell **shell);
t_node  *fix_redirection(t_node *list);
void    prt_list(t_minishell **shell);
void free_and_exit(t_minishell *shell);
void free_node(t_node *to_free);
>>>>>>> f26bb66 (new)
>>>>>>> 5213311 (new)
