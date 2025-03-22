/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:28:26 by asaadeh           #+#    #+#             */
/*   Updated: 2025/03/22 14:03:33 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

t_minishell *init_shell(t_minishell *shell)
{
    //shell = NULL;
    shell = malloc(sizeof(t_minishell));
    if (!shell)
    {
        perror("Memory allocation failed for shell.\n");
        return (NULL);
    }
    shell->token_list = NULL;
    // shell->cmd_list = NULL;
    shell->token_space = NULL;
    shell->name = NULL;
    return(shell);
}

t_node  *create_node_list(char **tokens) 
{
    int i = 0;
    t_node *head = NULL;
    t_node *current = NULL;

    while (tokens[i]) {
        // Ensure the token is valid before using it
        if (tokens[i] == NULL)
        {
            printf("Error: NULL token encountered at index %d\n", i);
            return (NULL);  // Return NULL if any token is invalid
        }
        t_node *new_node = malloc(sizeof(t_node));
        if (!new_node)
        {
            printf("Memory allocation failed\n");
            return (NULL);
        }
        new_node->node = NULL;
        new_node->node = ft_strdup(tokens[i]);
        if (!new_node->node)
        {
            free(new_node);
            printf("Memory allocation for node failed\n");
            return (NULL);
        }

        new_node->next = NULL;
        if (!head)
        {
            head = new_node;
            current = head;
        }
        else 
        {
            current->next = new_node;
            current = new_node;
        }
        i++;
    }
    return (head);
}

// void    init_cmd(t_cmd **cmd)
// {
//     t_cmd   *temp;

//     temp = NULL;
//     temp = malloc(sizeof(t_cmd));
//     if (!temp)
//     {
//         perror("failed to allocate structer command");
//         // free(temp);
//         return ;
//     }
//     temp->append = 0;
//     temp->file_in = NULL;
//     temp->file_out = NULL;
//     temp->pipe = NULL;
//     temp->args = NULL;
//     temp->args = (char **)malloc(sizeof(char *) * ARGS_MAX);
//     if (!temp->args)
//     {
//         perror("failed to allocate arguments");
//         free_cmd_list(temp);
//         return ;
//     }
//     temp->next = NULL;
//     (*cmd) = temp;
// }
