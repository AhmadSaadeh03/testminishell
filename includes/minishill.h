/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishill.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:10:19 by asaadeh           #+#    #+#             */
/*   Updated: 2025/03/01 15:45:20 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>
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
        char *name;
        char **token_space;
        t_node *token_list;
        t_tokentype *token_type;
}t_minishell;

int split_operation(t_minishell *shell, char operator);
t_node *create_node_list(char **tokens);
int split(t_minishell *shell);
int closed_quotes(t_minishell *shell, char qoute);
//void split_quotes(t_minishell *shell, char operator);
int split_space(t_minishell *shell);
int init_operation(t_minishell *shell);
int qoutes_handling(t_minishell *shell,char qoute);