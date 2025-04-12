/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:51:55 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/12 17:08:40 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishill.h"

void handle_export(char *str, t_env **env_list)
{
    char *equal;
    char *name;
    char *val;

    if (!str || !env_list)
        return;

    equal = ft_strchr(str, '=');
    if (equal)
    {
        name = ft_substr(str, 0, equal - str);     // extract before '='
        val = ft_strdup(equal + 1);                // extract after '='
        val = ft_trim_quotes(val);                 // remove quotes
    }
    else
    {
        name = ft_strdup(str);                     // just the name
        val = NULL;                                // no value
    }
    my_setenv(env_list, name, val);
    print_env_list(env_list);
    free(name);
    if (val) free(val);
}

void print_env_list(t_env **env_list)
{
    t_env *current;

    if (!env_list || !*env_list)
        return;

    current = *env_list;
    while (current)
    {
        if (current->value)
            printf("%s=\"%s\"\n", current->env_name, current->value);
        else
            printf("%s\n", current->env_name);
        current = current->next;
    }
}

