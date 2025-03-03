/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:42:38 by asaadeh           #+#    #+#             */
/*   Updated: 2025/03/03 15:44:45 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

int split_space(t_minishell *shell)
{
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
    int inside_quotes = 0;  // Flag to track if we are inside quotes
    temp = ft_strdup(shell->name);
    if (!temp)
        return 1;
    len = ft_strlen(temp);

    while (i < len)
    {
        if (temp[i] == operator && operator != '"')
        {
            if ((i == 0 || i == len - 1) && (operator == '|' || operator == '>' || operator == '<')) 
            {
                printf("syntax error near unexpected token\n");
                free(temp);
                return 1;
            }
            if (i > 0 && temp[i - 1] != ' ') 
            {
                new_len = len + 1; // Space before the operator
                char *new_temp = malloc(new_len + 1);
                if (!new_temp)
                {
                    free(temp);
                    return 1;
                }
                ft_memcpy(new_temp, temp, i);
                new_temp[i] = ' ';
                ft_memcpy(new_temp + i + 1, temp + i, len - i + 1);
                free(temp);
                temp = new_temp;
                len = new_len;
                i++; // Move index forward due to the inserted space
            }
            // Add space after operator if not present
            if (i + 1 < len && temp[i + 1] != ' ') 
            {
                new_len = len + 1;
                char *new_temp = malloc(new_len + 1);
                if (!new_temp)
                {
                    free(temp);
                    return 1;
                }
                ft_memcpy(new_temp, temp, i + 1);
                new_temp[i + 1] = ' ';
                ft_memcpy(new_temp + i + 2, temp + i + 1, len - i);
                free(temp);
                temp = new_temp;
                len = new_len;
            }
        }
        
        // Handle quotes and treat everything inside as one token
        if (temp[i] == '"' && operator == '"')
        {
            if (!inside_quotes)
            {
                // If we encounter the first quote, check if a space is needed before
                if (i > 0 && temp[i - 1] != ' ') 
                {
                    new_len = len + 1;
                    char *new_temp = malloc(new_len + 1);
                    if (!new_temp)
                    {
                        free(temp);
                        return 1;
                    }
                    ft_memcpy(new_temp, temp, i);
                    new_temp[i] = ' ';  // Add a space before the first quote
                    ft_memcpy(new_temp + i + 1, temp + i, len - i + 1);
                    free(temp);
                    temp = new_temp;
                    len = new_len;
                    i++; // Move index forward due to the inserted space
                }
                inside_quotes = 1;  // Flag set to true as we are inside quotes
            }
            else
            {
                // If we encounter the closing quote, check if space is needed after
                if (i + 1 < len && temp[i + 1] != ' ') 
                {
                    new_len = len + 1;
                    char *new_temp = malloc(new_len + 1);
                    if (!new_temp)
                    {
                        free(temp);
                        return 1;
                    }
                    ft_memcpy(new_temp, temp, i + 1);
                    new_temp[i + 1] = ' ';  // Add a space after the closing quote
                    ft_memcpy(new_temp + i + 2, temp + i + 1, len - i);
                    free(temp);
                    temp = new_temp;
                    len = new_len;
                }
                inside_quotes = 0;  // Reset flag as we are outside quotes now
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
        return 0;
    }
    while (shell->name[i])
    {
        if (shell->name[i] == '|' || shell->name[i] == '<' || shell->name[i] == '>' || shell->name[i] == '"')
        {
            if (split_operation(shell, shell->name[i]) == 1)
                return 1;
        }
        i++;
    }
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