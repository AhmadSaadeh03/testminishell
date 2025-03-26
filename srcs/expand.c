/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:29:12 by fghanem           #+#    #+#             */
/*   Updated: 2025/03/26 14:27:16 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

void    expand(t_minishell *shell)
{
    t_node  *temp;
    char    *new;
    t_env   *env_list;
    int     i;

    i = 0;
    env_list = copy_env_to_list();
    // print_env_list(env_list);
    temp = shell->token_list;
    while (temp)
    {
        if (temp->cmd_type == COMMAND && ft_strcmp(temp->node, "export") == 0 && temp->next)
        {
            temp = temp->next;
            
            // my_setenv(env_list, temp->)
        }
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

char    *handle_env(char *str, t_env *env_list)
{
    char    *new;
    char    *start;
    char    *sign;
    int     len_bef;
    char    *beff;
    char    *var_start;
    char    *var_end;
    int      var_len;
    char    *var_name;
    char    *var_val;

    new = ft_strdup("");
    start = str;
    sign = ft_strchr(start, '$');
    while(sign != NULL)
    {
        len_bef = sign - start;
        beff = ft_substr(start, 0, len_bef);
        new = ft_strjoin_free(new, beff);
        var_start = sign + 1;
        var_end = var_start;
        while(*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
            var_end++;
        var_len = var_end - var_start;
        var_name = ft_substr(var_start, 0, var_len);
        var_val = my_getenv(env_list, var_name);
        free(var_name);
        if(var_val)
            new = ft_strjoin_free(new, ft_strdup(var_val));
        start = var_end;
        sign = ft_strchr(start, '$');
    }
    new = ft_strjoin_free(new, ft_strdup(start));
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

t_env   *copy_env_to_list()
{
    extern  char    **environ;
    t_env   *head;
    t_env   *tail;
    int     i;
    t_env   *new_node;  

    head = NULL;
    tail = NULL;
    i = 0;
    while(environ[i])
    {
        new_node = create_env(environ[i]);
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
