/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:28:26 by asaadeh           #+#    #+#             */
/*   Updated: 2025/03/01 16:32:38 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

t_node *create_node_list(char **tokens) 
{
    int i = 0;
    t_node *head = NULL;
    t_node *current = NULL;

    while (tokens[i]) {
        // Ensure the token is valid before using it
        if (tokens[i] == NULL) {
            printf("Error: NULL token encountered at index %d\n", i);
            return NULL;  // Return NULL if any token is invalid
        }

        t_node *new_node = malloc(sizeof(t_node));
        if (!new_node) {
            printf("Memory allocation failed\n");
            return NULL;
        }

        new_node->node = ft_strdup(tokens[i]);
        if (!new_node->node) {
            free(new_node);
            printf("Memory allocation for node failed\n");
            return NULL;
        }

        new_node->next = NULL;
        if (!head) {
            head = new_node;
            current = head;
        } else {
            current->next = new_node;
            current = new_node;
        }
        i++;
    }
    return head;
}
