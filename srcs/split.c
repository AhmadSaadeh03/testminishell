/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:42:38 by asaadeh           #+#    #+#             */
/*   Updated: 2025/02/25 12:45:40 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"
// int split_space(t_minishell *shell)
// {
//     shell->token_space = ft_split(shell->name, ' ');
//     if (shell->token_space != NULL)
//     {
//         t_node *head = create_node_list(shell->token_space);
//         if (!head)
//                 return 1;
//         t_node *current = head;
//         while (current != NULL)
//         {
//             printf("%s", current->node); 
//             if (current->next != NULL)
//                 printf(" -> ");
//             current = current->next;
//         }
//         printf(" -> NULL\n");
//         current = head;
//         while (current != NULL)
//         {
//             t_node *temp = current;
//             current = current->next;
//             free(temp->node);
//             free(temp);
//         }
//         int i = 0;
//         while (shell->token_space[i])
//         {
//             free(shell->token_space[i]);
//             i++;
//         }
//         free(shell->token_space);
//     }
//     return 0;
// }
int split_space(t_minishell *shell)
{
    shell->token_space = ft_split(shell->name, ' ');
    if (shell->token_space != NULL)
    {
        t_node *head = create_node_list(shell->token_space);
        if (!head)
            return 1;
        return 0;
    }
    return 1;
}

int split_pipe(t_minishell *shell, char operator)
{
    char *temp;
    
    temp = ft_strdup(shell->name);
    if (!temp)
        return 1;
    int i = 0;
    int len = ft_strlen(temp);
    while (temp[i])
    {
        if (temp[i] == operator)
        {
            // If the pipe is at the beginning or end of the string, add spaces accordingly
            if (temp[0] == operator || temp[len - 1] == operator) // If there is a pipe in the first of string is error or al the last it's open a quote.
            {
                printf("%s\n", "syntax error near unexpected token");
                exit(1);
            }
            if (i > 0 && temp[i - 1] != ' ' && (temp[i-1]!= ' ' || temp[i + 1] != ' '))  // Add space before pipe if not already there
            {
                // Shift the characters to the right to make space
                ft_memmove(temp + i + 1, temp + i, len - i + 1);  // Shift right by 1
                temp[i] = ' ';  // Insert space before pipe
                len++;  // Increase length of the string since we added a space
                i++;  // Move forward to avoid infinite loop due to the new space
            }
            if (i + 1 < len && temp[i + 1] != ' ')  // Add space after pipe if not already there
            {
                // Shift characters to the right by 1 to make space for the space after the pipe
                ft_memmove(temp + i + 2, temp + i + 1, len - i);  // Shift right by 1
                temp[i + 1] = ' ';
                len++;
            }
        }
        i++;
    }
    split_space(shell);
    free(shell->name);
    shell->name = temp;
    return 0;
}

int split(t_minishell *shell)
{
    int i = 0;
    int inside_qoute = 0;
    if (!*shell->name)
        return 1;
    while (shell->name[i])
    {
        if (shell->name[i] == 39 || shell->name[i] == 34)
        {
            if (!closed_quotes(shell, shell->name[i])) // check if the qoutes is closed the function is in checks.c if it returns 1 this means it's closed else is error
            {
                printf("%s\n", "Invalid quotes");
                exit(1);
            }
            inside_qoute = !inside_qoute;
            split_quotes(shell, shell->name[i]);
        }
        if (shell->name[i] == ' ' && !inside_qoute)
        {
            split_space(shell);
        }
        if (shell->name[i] == '|' || shell->name[i] == '<' || shell->name[i] == '>')
        {
            split_pipe(shell, shell->name[i]);
        }
        i++;
    }
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

t_node *create_node_list(char **tokens)
{
    int i = 0;
    t_node *head = NULL;
    t_node *current = NULL;
    while (tokens[i])
    {
        t_node *new_node = malloc(sizeof(t_node));
        if (!new_node)
            return NULL;
        new_node->node = ft_strdup(tokens[i]);
        if (!new_node->node)
        {
            free(new_node);
            return NULL;
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
    return head;
}
