/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/01 16:37:34 by asaadeh          ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2025/03/03 10:39:40 by fghanem          ###   ########.fr       */
=======
/*   Updated: 2025/03/08 14:20:48 by fghanem          ###   ########.fr       */
>>>>>>> f26bb66 (new)
>>>>>>> 5213311 (new)
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

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
<<<<<<< HEAD
    return 0;
<<<<<<< HEAD
}
=======
=======
    return (0);
>>>>>>> f26bb66 (new)
}
>>>>>>> 5213311 (new)
