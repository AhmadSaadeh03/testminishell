/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishill.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:10:19 by asaadeh           #+#    #+#             */
/*   Updated: 2025/03/03 15:31:17 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>

typedef enum s_type
{
    TOKEN_PIPE, // | 0
	TOKEN_WORD, // CMD, ARG 1
	TOKEN_REDIRECT_IN, // < 2
	TOKEN_REDIRECT_OUT, // > 3
	TOKEN_APPEND, // >> 4
	TOKEN_HEREDOC, // << 5
    // FILEIN, // 6
    // COMMAND, // 7
    // FILEOUT, // 8
    
}   t_type;

typedef struct s_cmd
{
    char    **args;
    char    *file_in;
    char    *file_out;
    struct s_cmd    *next;
}   t_cmd;

typedef struct s_node
{
    char *node;
    struct s_node *next;
    t_type          cmd_type;
}   t_node;

typedef struct s_token
{
    char pipe;
    char *append; // >>
    char redirect_out; //>
    char redirect_in; //<
    char  *quoted;
}   t_tokentype;

typedef struct s_minishell
{
        char *name;
        char **token_space;
        t_node *token_list;
        t_tokentype *token_type;
        t_cmd       **cmd_list;
}   t_minishell;

int split_operation(t_minishell *shell, char operator);
t_node *create_node_list(char **tokens);
int split(t_minishell *shell);
int closed_quotes(t_minishell *shell, char qoute);
//void split_quotes(t_minishell *shell, char operator);
int split_space(t_minishell *shell);
int init_operation(t_minishell *shell);
int qoutes_handling(t_minishell *shell,char qoute);

void    parsing(t_minishell **shell);
void    init_cmd(t_cmd **cmd);
// void    print(t_minishell **shell);
void    print(t_minishell **shell);