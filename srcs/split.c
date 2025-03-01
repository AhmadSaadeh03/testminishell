/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:42:38 by asaadeh           #+#    #+#             */
/*   Updated: 2025/03/01 16:55:35 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

int split_space(t_minishell *shell)
{
    shell->token_space = &shell->name;
    shell->token_space = ft_split(shell->name, ' ');
    if (!shell->token_space) {
        printf("Error: Failed to split the input\n");
        return 1;
    }
    return 0;   
}

int split_operation(t_minishell *shell, char operator)
{
    char *temp;
    int i = 0, len, new_len;
    temp = ft_strdup(shell->name);
    if (!temp)
        return 1;
    len = ft_strlen(temp);
    while (i < len)
    {
        if (temp[i] == operator)
        {
            if (i == 0 || i == len - 1) 
            {
                printf("%s\n", "syntax error near unexpected token");
                free(temp);
                return 1;
            }
            if (i > 0 && temp[i - 1] != ' ') 
            {
                // Create a new string with extra space for the new space
                new_len = len + 1; // Space before the operator
                char *new_temp = malloc(new_len + 1);
                if (!new_temp)
                {
                    free(temp);
                    return 1; // Memory allocation error
                }
                // Copy the part before the operator and the space
                ft_memcpy(new_temp, temp, i);
                new_temp[i] = ' '; // Add space
                ft_memcpy(new_temp + i + 1, temp + i, len - i + 1);
                free(temp);
                temp = new_temp;
                len = new_len;
                i++; // Move index forward due to the inserted space
            }
            // Add space after operator if not present
            if (i + 1 < len && temp[i + 1] != ' ') 
            {
                new_len = len + 1; // Space after the operator
                char *new_temp = malloc(new_len + 1);
                if (!new_temp)
                {
                    free(temp);
                    return 1; // Memory allocation error
                }
                // Copy the part before the operator, add space, and then the rest
                ft_memcpy(new_temp, temp, i + 1);
                new_temp[i + 1] = ' ';
                ft_memcpy(new_temp + i + 2, temp + i + 1, len - i);
                free(temp);
                temp = new_temp;
                len = new_len;
            }
        }
        i++;  // Move to the next character
    }
    free(shell->name);
    shell->name = temp;
    return 0;
}
int split(t_minishell *shell)
{
    int i = 0;
    if (!*shell->name || !shell->name)
    {
        return 1;
    }
    while (shell->name[i])
    {
        if (shell->name[i] == '|' || shell->name[i] == '<' ||shell->name[i] == '>'|| shell->name[i] == '-')
        {
            if (split_operation(shell, shell->name[i]) == 1)
                return 1;
        }
        if (shell->name[i] == 34)
        {
            if (!closed_quotes(shell, shell->name[i])) // check if the qoutes is closed the function is in checks.c if it returns 1 this means it's closed else is error
            {
                printf("%s\n", "Invalid quotes");
                return 1;
            }
           qoutes_handling(shell,shell->name[i]);
        }    
        i++;
    }
    //split_space(shell);
    if (split_space(shell) == 1)
        return 1;
    
    t_node *head = create_node_list(shell->token_space);
    if (head)
    {
        t_node *current = head;
        while (current != NULL)
        {
            printf("%s", current->node);
            if (current->next != NULL)
                printf(" -> ");
            current = current->next;
        }
        printf(" -> NULL\n");
        current = head;
        while (current != NULL)
        {
            t_node *temp = current;
            current = current->next;
            free(temp->node);
            free(temp);
        }
    }
    i = 0;
    while (shell->token_space[i])
    {
        free(shell->token_space[i]);
        i++;
    }
    free(shell->token_space);
    return 0;
} 