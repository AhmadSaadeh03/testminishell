/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:29:12 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/09 13:35:43 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

void    expand(t_minishell *shell, t_env *env_list)
{
    t_node  *temp;
    char    *new;
    int     i;

    i = 0;
    temp = shell->token_list;
    while (temp)
    {
        // if (temp->cmd_type == COMMAND && ft_strcmp(temp->node, "export") == 0 && temp->next)
        // {
        //     temp = temp->next;
            
        //     // my_setenv(env_list, temp->)
        // }
        if (temp->cmd_type == TOKEN_ARG)
        {
            if (temp->node[0] == '"')
            {
                new = ft_trim_quotes(temp->node);
                if(!new)
                    return ;
                i = 1;
                free(temp->node);
                temp->node = handle_env(new, env_list);
                if(temp->node)
                    printf("%s\n", temp->node);
            }
            else if (temp->node[0] == 39)
            {
                new = ft_trim_quotes(temp->node);
                if(!new)
                    return ;
                free(temp->node);
                temp->node = ft_strdup(new);
                if(temp->node)
                    printf("%s\n", temp->node);
            }
            else
            {
                new = ft_strdup(temp->node);
                free(temp->node);
                temp->node = handle_env(new, env_list);
                if(temp->node)
                    printf("%s\n", temp->node);
            }
        }
        temp = temp->next;
    }
}

char    *my_getenv(t_env *env_list, char *name)
{
        t_env   *temp;
        temp = env_list;
        while (temp)
        {
                if (ft_strcmp(temp->env_name, name) == 0)
                {
                        return (temp->value);
                }
                temp = temp->next;
        }
        return (NULL);
}

void    my_setenv(t_env **env_list, char *name, char *value, int overwrite)
{
        t_env   *temp;
        t_env   *new_node;

        temp = *env_list;
        while (temp)
        {
                if (ft_strcmp(temp->env_name, name) == 0)
                {
                        if (overwrite)
                        {
                                free(temp->value);
                                temp->value = ft_strdup(value);
                        }
                        return ;
                }
                temp = temp->next;
        }
        new_node = malloc(sizeof(t_env));
        if (!new_node)
                return ;
        new_node->env_name = ft_strdup(name);
        new_node->value = ft_strdup(value);
        new_node->next = *env_list;
        *env_list = new_node;
}
