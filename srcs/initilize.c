/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:28:26 by asaadeh           #+#    #+#             */
/*   Updated: 2025/04/09 13:29:33 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

t_minishell *init_shell(t_minishell *shell)
{
    shell = malloc(sizeof(t_minishell));
    if (!shell)
    {
        perror("Memory allocation failed for shell.\n");
        return (NULL);
    }
    shell->token_list = NULL;
    shell->token_space = NULL;
    shell->name = NULL;
    return (shell);
}

t_node *create_node_list(char **tokens)
{
    int i = 0;
    t_node *head;
    t_node *current;

    current = NULL;
    head = NULL;
    while (tokens[i])
    {
        if (tokens[i] == NULL)
        {
            printf("Error: NULL token encountered at index %d\n", i);
            return NULL;
        }
        t_node *new_node;

        new_node = create_new_node(tokens[i]);
        if (!new_node)
            return NULL;
        append_node(&head, &current, new_node);
        i++;
    }
    return (head);
}

void append_node(t_node **head, t_node **current, t_node *new_node)
{
    if (!*head)
    {
        *head = new_node;
        *current = new_node;
    }
    else
    {
        (*current)->next = new_node;
        *current = new_node;
    }
}

t_node *create_new_node(char *token)
{
    t_node *new_node;

    new_node = malloc(sizeof(t_node));
    if (!new_node)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    new_node->node = ft_strdup(token);
    if (!new_node->node)
    {
        free(new_node);
        printf("Memory allocation for node failed\n");
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}
