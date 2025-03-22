/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:29:12 by fghanem           #+#    #+#             */
/*   Updated: 2025/03/22 15:47:12 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

void    expand(t_minishell *shell)
{
    t_node  *temp;
    int     i;

    i = 0;
    temp = shell->token_list;
    while (temp)
    {
        if (temp->cmd_type == TOKEN_ARG)
        {
            if (temp->node[0] == '$' && temp->node[1] != '$' && temp->node[1] != '?' && temp->node[1] != '0')
            {
                char *new = ft_substr((temp->node), 1, (ft_strlen(temp->node) - 1));
                char *value = getenv(new);
                free(temp->node);
                temp->node = ft_strdup(value);
                if(temp->node)
                    printf("%s\n", temp->node);
            }
            else if (ft_strcmp(temp->node, "$$") == 0)
            {
                char *new = ft_itoa(getpid());
                free(temp->node);
                temp->node = ft_strdup(new);
                if(temp->node)
                    printf("%s\n", temp->node);
            }
            else if (ft_strcmp(temp->node, "$0") == 0)
            {
                char *new = getenv("0");
                // if(!new)
                free(temp->node);
                temp->node = ft_strdup(new);
                if(temp->node)
                    printf("%s\n", temp->node);
            }
        }
        temp = temp->next;
    }
}
