/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:29:12 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/12 17:13:15 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishill.h"

void expand(t_minishell *shell,t_env *env_list)
{
    t_node *temp;
    char *new;
    //t_env *env_list;

    //env_list = copy_env_to_list();
    temp = shell->token_list;

    while (temp)
    {
        if(ft_strcmp(temp->node, "export") == 0 && temp->next) 
        {
                temp = temp->next;
                handle_export(temp->node ,&env_list);
        }
        if (temp->cmd_type == TOKEN_ARG)
        {
            // Step 1: Handle environment variables
            new = handle_env(temp->node, env_list);
            if (!new)
                return;

            // Step 2: Remove quotes
            char *final = ft_trim_quotes(new);
            free(new); // Free the intermediate string
            if (!final)
                return;
                
            // Update the node with the final processed string
            free(temp->node);
            temp->node = final;
            if (temp->node)
                printf("%s\n", temp->node);
        }
        temp = temp->next;

    }
    print_env_list(&env_list);
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

void    my_setenv(t_env **env_list, char *name, char *value)
{
        t_env   *temp;
        t_env   *new_node;

        temp = *env_list;
        while (temp)
        {
                if (ft_strcmp(temp->env_name, name) == 0)
                {
                        free(temp->value);
                        temp->value = ft_strdup(value);
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
