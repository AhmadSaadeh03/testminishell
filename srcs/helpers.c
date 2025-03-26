/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:42:51 by fghanem           #+#    #+#             */
/*   Updated: 2025/03/26 14:08:10 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

char    *ft_trim_quotes(char *s1)
{
        int             start;
        int             end;

        if (!s1)
                return (NULL);
        start = 0;
        end = ft_strlen(s1) - 1;
        if (end < 0)
                return (ft_strdup(""));
        if ((s1[start] == '"' && s1[end] == '"') || (s1[start] == '\'' && s1[end] == '\''))
        {
                start++;
                end--;
        }
        return (ft_substr(s1, start, end - start + 1));
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

void print_env_list(t_env *env_list) {
        while (env_list) {
                printf("%s=%s\n", env_list->env_name, env_list->value);
                env_list = env_list->next;
        }
}