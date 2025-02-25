/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishill.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:10:19 by asaadeh           #+#    #+#             */
/*   Updated: 2025/02/25 12:45:27 by fghanem          ###   ########.fr       */
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
typedef struct s_minishell
{
        char *name;
        char **token_space;
        t_node *token_list; 
       char  **token_pipe;
       char  *quoted;
}t_minishell;

int split_pipe(t_minishell *shell, char operator);
t_node *create_node_list(char **tokens);
int split(t_minishell *shell);
int closed_quotes(t_minishell *shell, char qoute);
void split_quotes(t_minishell *shell, char operator);
int split_space(t_minishell *shell);