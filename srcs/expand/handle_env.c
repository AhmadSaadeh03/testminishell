/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:49:32 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/10 18:37:33 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishill.h"

char *handle_env(char *str, t_env *env_list)
{
    char *new;
    char *start;
    char *sign;
    int in_single_quotes = 0;
    int in_double_quotes = 0;

    new = ft_strdup("");
    start = str;

    while (*start)
    {
        if (*start == '\'') // Handle single quotes
        {
            if (!in_double_quotes) // Toggle single quotes only if not inside double quotes
                in_single_quotes = !in_single_quotes;
            else // If inside double quotes, preserve the single quote
                new = ft_strjoin_free(new, ft_substr(start, 0, 1));
            start++; // Skip the single quote
        }
        else if (*start == '"') // Handle double quotes
        {
            if (!in_single_quotes) // Toggle double quotes only if not inside single quotes
                in_double_quotes = !in_double_quotes;
            else // If inside single quotes, preserve the double quote
                new = ft_strjoin_free(new, ft_substr(start, 0, 1));
            start++; // Skip the double quote
        }
        else if (*start == '$' && !in_single_quotes) // Expand only if not in single quotes
        {
            sign = start;
            start++; // Skip the '$'
            char *var_start = start;
            while (*start && (ft_isalnum(*start) || *start == '_'))
                start++;
            char *var_name = ft_substr(var_start, 0, start - var_start);
            char *var_val = my_getenv(env_list, var_name);
            free(var_name);
            if (var_val)
                new = ft_strjoin_free(new, ft_strdup(var_val));
            else // If variable is not found, keep it as-is
                new = ft_strjoin_free(new, ft_substr(sign, 0, start - sign));
        }
        else // Handle literal characters
        {
            new = ft_strjoin_free(new, ft_substr(start, 0, 1));
            start++;
        }
    }
    return (new);
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
