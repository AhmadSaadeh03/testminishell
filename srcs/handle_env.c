/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:49:32 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/09 13:40:14 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

char    *handle_env(char *str, t_env *env_list)
{
    char *res;
    char *cur;
    char *dollar;
    char    *var;
    int len;
    char    *name;
    char    *val;

    res = ft_strdup("");
    cur = str;
    while ((dollar = ft_strchr(cur, '$')))
    {
        res = ft_strjoin_free(res, ft_substr(cur, 0, dollar - cur));
        var = dollar + 1;
        len = 0;
        while (ft_isalnum(var[len]) || var[len] == '_')
            len++;
        name = ft_substr(var, 0, len);
        val = my_getenv(env_list, name);
        free(name);
        if (val)
            res = ft_strjoin_free(res, ft_strdup(val));
        cur = var + len;
    }
    return ft_strjoin_free(res, ft_strdup(cur));
}

char    *ft_strjoin_free(char *s1, char *s2)
{
    size_t  len1;
    size_t  len2;
    char    *joined;

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    joined = malloc(len1 + len2 + 1);
    if (!joined)
        return(NULL);
    ft_strcpy(joined, s1);
    ft_strcat(joined, s2);
    free(s1);
    free(s2);
    return(joined);
}

t_env   *copy_env_to_list(char **envp)
{
    t_env   *head;
    t_env   *tail;
    int     i;
    t_env   *new_node;  

    head = NULL;
    tail = NULL;
    i = 0;
    while(envp[i])
    {
        new_node = create_env(envp[i]);
        if (!new_node)
        {
            i++;
            continue;
        }
        if (!head)
            head = new_node;
        else
            tail->next = new_node;
        tail = new_node;
        i++;
    }
    return (head);
}

t_env   *create_env(char *env_var)
{
    t_env   *node;
    char    *sign_equal;

    node = malloc(sizeof(t_env));
    if (!node)
        return (NULL);
    sign_equal = ft_strchr(env_var, '=');
    if (!sign_equal)
    {
        free(node);
        return (NULL);
    }
    *sign_equal = '\0';
    node->env_name = ft_strdup(env_var);
    node->value = ft_strdup(sign_equal + 1);
    *sign_equal = '=';
    node->next = NULL;
    return (node);
}
