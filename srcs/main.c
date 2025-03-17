/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/03/17 12:43:26 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"


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

#include <stdlib.h>
#include <string.h>

void ahmad(t_cmd **cmd)
{
    t_cmd *temp;

    // Allocate memory for the t_cmd structure
    temp = malloc(sizeof(t_cmd));
    if (!temp)
    {
        perror("Memory allocation failed for command structure");
        return;
    }

    // Initialize fields to default values
    temp->args = NULL;       // No arguments initially
    temp->file_in = NULL;    // No input file initially
    temp->file_out = NULL;   // No output file initially
    temp->redirect = NULL;   // No redirection initially
    temp->append = 0;        // Append flag initially set to 0
    temp->pipe = NULL;       // No pipe initially
    temp->next = NULL;       // No next command initially

    *cmd = temp;  // Set the caller's pointer to the newly initialized structure
}

int main(void)
{
    t_minishell *shell = NULL;

    shell = init_shell(shell);
    if (!shell)
    {
        printf("ERROR:%s \n", "fail allocation of shell");
        exit(1);
    }
    while (1)
    {
        shell->name = readline("👾 Minihell> ");
        if(*(shell->name) == '\0') /////// to keep the minishell in prompt
        {
            free(shell->name);
            continue ;
        }
        add_history(shell->name);
        if (split(shell) == 1)
            free_minishell(shell);
        free(shell->name);
    }
    free_and_exit(shell);
    return (0);
}

// int main()
// {
//     //t_cmd *cmd = init_cmd();
//     //  if (cmd == NULL)
//     //     return 1;
//     t_minishell *shell = NULL;
//     char *str = "sas|saddasd";
//     shell = init_shell(shell);
//     if (!shell)
//     {
//         printf("xxx");
//         exit(1);
//     }
//     shell->name = ft_strdup(str);
//     if (!shell->name)
//     {
//         printf("ERROR: Memory allocation failed\n");
//         free_and_exit(shell);
//     }
//         if (*(shell->name) == '\0')
//         {
//              printf("xxx");
//             free(shell->name);
//             shell->name = NULL;
//         }
//         if (split(shell) == 1)
//         {
//              printf("xxx");
//             free_minishell(shell);
//             return (0);
//         }
//     free(shell->name);
//     shell->name = NULL;
//     free_and_exit(shell);
//    // free(cmd->args);
//     //free(cmd);
//     return (0);
// }

