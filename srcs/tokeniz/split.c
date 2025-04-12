/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:32:34 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/10 18:36:57 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishill.h"

int split_space(t_minishell *shell)
{
    char *temp;

    temp = replace_spaces_inside_quotes(shell->name);
    if (!temp)
        return 1;
    shell->token_space = ft_split(temp, ' ');
    free(temp);
    if (!shell->token_space)
    {
        printf("Error: Failed to split the input\n");
        return 1;
    }
    restore_spaces(shell->token_space);
    return 0;
}

int split_operation(t_minishell *shell, char operator)
{
    int i;
    int len;
    char *temp;
    
    i = 0;
    temp = ft_strdup(shell->name);
    if (!temp)
        return (1);
    len = ft_strlen(temp);
    while (i < len)
    {
        if (temp[i] == operator)
        {
            if (i > 0 && temp[i - 1] != ' ')
            {
                temp = space_before_op(temp, i, &len);
                if (!temp)
                    return (1);
                i++;
            }
            if (i + 1 < len && temp[i + 1] != ' ')
            {
                temp = space_after_op(temp, i, &len);
                if (!temp)
                    return (1);
            }
        }
        i++;
    }
    free(shell->name);
    shell->name = temp;
    return (0);
}

int split(t_minishell *shell)
{
    if (!*shell->name || !shell->name)
        return (1);
    if (handle_quotes_and_operators(shell))
        return (1);
    if (split_space(shell) == 1)
        return (1);
    process_node_list(shell);
    return (0);
}

int handle_quotes_and_operators(t_minishell *shell)
{
    int i = 0;

    while (shell->name[i])
    {
        if (shell->name[i] == '\'' || shell->name[i] == '"')
        {
            if (closed_quotes(shell, shell->name[i]) == 1)
            {
                printf("Error: Unclosed quotes\n");
                return (1);
            }
            i = handle_quote(shell, shell->name[i]) + i + 1;
        }
        if (shell->name[i] == '|' || shell->name[i] == '<' || shell->name[i] == '>')
        {
            if (handle_operation(shell) == 1)
                return (1);
            if (split_operation(shell, shell->name[i]) == 1)
                return (1);
        }
        i++;
    }
    return (0);
}


void process_node_list(t_minishell *shell)
{
    t_node *temp;

    shell->token_list = create_node_list(shell->token_space);
    if (shell->token_list && shell->token_list->next == NULL && shell->token_list->node && 
    (shell->token_list->node[0] == '|' || shell->token_list->node[0] == '<' || shell->token_list->node[0] == '>'))
    {
        printf("minishell: syntax error near unexpected token `|'\n");
        return ;
    }
    temp = shell->token_list;
    while (temp->next)
        temp = temp->next;
    if ((ft_strcmp(temp->node,">") == 0 || ft_strcmp(temp->node,"<") == 0|| ft_strcmp(temp->node,"|") == 0 )
    && temp->next == NULL)
    {
        printf("syntax error near unexpected token\n");
        return;
    }
    free_token_space(shell->token_space);
    if(parsing(&shell) == 1)
        return ;
}
