/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:42:38 by asaadeh           #+#    #+#             */
/*   Updated: 2025/02/24 16:07:45 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

int split_space(t_minishell *shell)
{
    shell->token_space = ft_split(shell->name, ' ');
    if (shell->token_space != NULL)
    {
        t_node *head = create_node_list(shell->token_space);
        if (!head)
                return 1;
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
        int i = 0;
        while (shell->token_space[i])
        {
            free(shell->token_space[i]);
            i++;
        }
        free(shell->token_space);
    }
    return 0;
}
int split_pipe(t_minishell *shell)
{
    shell->token_pipe = ft_split(shell->name,'|');
    if (shell->token_pipe != NULL)
    {
        t_node *head = create_node_list(shell->token_pipe);
        if (!head)
                return 1;
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
        int i = 0;
        while (shell->token_pipe[i])
        {
            free(shell->token_pipe[i]);
            i++;
        }
        free(shell->token_pipe);
    }
    return 0;
        
}

int split(t_minishell *shell)
{
        int i = 0;
        while (shell->name[i])
        {
                if (ft_strncmp(&shell->name[i]," ",ft_strlen(shell->name))!=0)
                {
                        split_space(shell);
                        break;
                }
                if (ft_strncmp(&shell->name[i],"|",ft_strlen(shell->name))!=0)
                {
                        printf("ahmad");
                        shell->name[i-1] = ' ';
                        shell->name[i+1] = ' ';
                        split_space(shell);
                        break;
                }
                i++;
        }
        return 1;
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