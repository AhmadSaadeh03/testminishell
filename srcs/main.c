/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/03/10 14:39:12 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

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
        if (split(shell) == 1)
        {
            free(shell->name);
            free(shell);
            return 1;
        }
        free(shell->name);
    }
    free(shell);
    return 0;
}
// int main(void)
// {
//     t_minishell *shell = NULL;

//     shell = init_shell(shell);
//     while (1)
//     {
//         shell->name = readline("🤡 CTRL+Z > ");
//         if(*(shell->name) == '\0') /////// to keep the minishell in prompt
//             free(shell->name);
//         add_history(shell->name);
//         if (split(shell) == 1)
//             free_minishell(shell);
//         free(shell->name);
//     }
//     free(shell);
//     return (0);
// }