/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishill.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:10:19 by asaadeh           #+#    #+#             */
/*   Updated: 2025/02/24 19:02:32 by asaadeh          ###   ########.fr       */
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
}t_minishell;
int split_space(t_minishell *shell);
t_node *create_node_list(char **tokens);
int split(t_minishell *shell);