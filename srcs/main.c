/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/03/10 13:26:23 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

int init_token(t_tokentype *token)
{
    if (!token)
        return 0;  // Return failure if the token pointer is NULL
    //token = malloc(sizeof(t_tokentype));
    // Initialize primitive types
    token->pipe = '\0';
    token->redirect_out = '\0';
    token->redirect_in = '\0';

    // Initialize pointers to NULL
    token->append = NULL;
    token->quoted = NULL;

    return 1;  // Return success
}

// int main(void)
// {
//     t_minishell *shell = NULL;
//     shell = malloc(sizeof(t_minishell));
//     if (!shell)
//     {
//         printf("Memory allocation failed for shell.\n");
//         return 1;
//     }

//     while (1)
//     {
//         shell->name = readline("minihell > ");
//         if (shell->name == NULL)
//         {
//             break;
//         }
//         add_history(shell->name);
//         shell->token_type = malloc(sizeof(t_tokentype));
//         if (!shell->token_type)
//         {
//             printf("Memory allocation failed for token_type.\n");
//             free(shell->name);
//             free(shell);
//             return 1;
//         }
//         if (init_token(shell->token_type) == 0)
//         {
//             free(shell->name);
//             free(shell->token_type);
//             free(shell);
//             return 1;
//         }
//         if (split(shell) == 1)
//         {
//             free(shell->name);
//             free(shell->token_type);
//             free(shell);
//             return 1;
//         }
//         free(shell->name);
//         free(shell->token_type);
//     }
//     free(shell);
//     return 0;
// }
int main(void)
{
    t_minishell *shell = NULL;

    shell = init_shell(shell);
    while (1)
    {
        shell->name = readline("🤡 CTRL+Z > ");
        if(*(shell->name) == '\0') /////// to keep the minishell in prompt
        {
            free(shell->name);
            continue ;
        }
        add_history(shell->name);
        shell->token_type = malloc(sizeof(t_tokentype));
        if (!shell->token_type)
        {
            perror("Memory allocation failed for token_type.\n");
            free_minishell(shell);
        }
        if (init_token(shell->token_type) == 0)
        {
            free_minishell(shell);
            continue ;
        }
        if (split(shell) == 1)
        {
            free_minishell(shell);
            continue ;
        }
        free(shell->name);
        free(shell->token_type);
    }
    free(shell);
    return (0);
}