/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:36:10 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/10 18:37:23 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishill.h"

void free_node(t_node *to_free)
{
    free(to_free->node);
    free(to_free);
}

void free_token_space(char **token_space)
{
    int i = 0;

    if (!token_space)
        return;
    while (token_space[i])
        free(token_space[i++]);
    free(token_space);
}

void free_minishell(t_minishell *shell)
{
    if (!shell)
        return;
    free_token_space(shell->token_space);
    free_tokens(shell->token_list);
    free(shell->name);
    free(shell);
}

void free_and_exit(t_minishell *shell)
{
    free_minishell(shell);
    exit(1);
}

void    free_tokens(t_node *list)
{
    t_node  *tmp;

    while (list)
    {
        tmp = list;
        list = list->next;
        free(tmp->node);
        free(tmp);
    }
}
