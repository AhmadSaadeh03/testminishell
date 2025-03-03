/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/03/03 10:39:40 by fghanem          ###   ########.fr       */
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
//     while (1)
//     {
//         shell->name = readline("minihell > ");
//         if (shell->name == NULL) 
//         {
//             break;
//         }
//         add_history(shell->name);
//        // split(shell);
//        init_token(shell);
//         if (split(shell) == 1)
//             return 1;
//        // init_operation(shell);
//         // if (!&split)
//         //         return 1;
//         free(shell->name);
//         free(shell->token_type);
//     }
//     return 0;
// }
int main(void)
{
    t_minishell *shell = NULL;
    shell = malloc(sizeof(t_minishell));
    if (!shell)
    {
        printf("Memory allocation failed for shell.\n");
        return 1;
    }

    while (1)
    {
        shell->name = readline("minihell > ");
        if (shell->name == NULL)
        {
            break;
        }
        add_history(shell->name);
        shell->token_type = malloc(sizeof(t_tokentype));
        if (!shell->token_type)
        {
            printf("Memory allocation failed for token_type.\n");
            free(shell->name);
            free(shell);
            return 1;
        }
        if (init_token(shell->token_type) == 0)
        {
            free(shell->name);
            free(shell->token_type);
            free(shell);
            return 1;
        }
        if (split(shell) == 1)
        {
            free(shell->name);
            free(shell->token_type);
            free(shell);
            return 1;
        }
        free(shell->name);
        free(shell->token_type);
    }
    free(shell);
    return 0;
}
