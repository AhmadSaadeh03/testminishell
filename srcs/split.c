/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:32:34 by fghanem           #+#    #+#             */
/*   Updated: 2025/03/26 14:43:01 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

int split_space(t_minishell *shell)
{
    int i = 0;
    int  j = 0;
    int inside_quotes_double = 0;
    int inside_quotes_single = 0;
    char *temp = (char *)malloc(sizeof(char) * (ft_strlen(shell->name) + 1));
    
    if (!temp)
        return 1;
    while (shell->name[i])
    {
        if (shell->name[i] == '"' && !inside_quotes_double && !inside_quotes_single) 
            inside_quotes_double = !inside_quotes_double;  // Toggle double quote state
        else if (shell->name[i] == '"' && inside_quotes_double) 
            inside_quotes_double = !inside_quotes_double;
        if (shell->name[i] == 39 && !inside_quotes_single && !inside_quotes_double) 
            inside_quotes_single = !inside_quotes_single;  // Toggle single quote state
        else if (shell->name[i] == 39 && inside_quotes_single) 
            inside_quotes_single = !inside_quotes_single;
        if (shell->name[i] == ' ' && (inside_quotes_single || inside_quotes_double))
            temp[j++] = '\a';  // Replace space with a non-printable character inside quotes
        else 
            temp[j++] = shell->name[i];
        i++;
    }
    temp[j] = '\0';
    shell->token_space = ft_split(temp, ' ');
    if (!shell->token_space) {
        printf("Error: Failed to split the input\n");
        free(temp);
        return 1;
    }
    // Restore spaces inside quotes
    i = 0;
    while (shell->token_space[i])
    {
        j = 0;
        while (shell->token_space[i][j])
        {
            if (shell->token_space[i][j] == '\a')
                shell->token_space[i][j] = ' ';
            j++;
        }
        i++;
    }
    free(temp);
    return 0;   
}

int split_operation(t_minishell *shell, char operator)
{
    char *temp;
    int i = 0, len, new_len;
    // int inside_quotes = 0;  // Flag to track if we are inside quotes
    temp = ft_strdup(shell->name);
    if (!temp)
        return 1;
    len = ft_strlen(temp);
    while (i < len)
    {
        if (temp[i] == operator)
        {
            // if ((i == 0 || i == len - 1) && (operator == '|')) 
            // {
            //     printf("syntax error near unexpected token\n");
            //     //free(temp);
            //     return 1;
            // }
            if (i > 0 && temp[i - 1] != ' ') 
            {
                new_len = len + 1; // Space before the operator
                char *new_temp = malloc(new_len + 1);
                if (!new_temp)
                {
                    free(temp);
                    return 1;
                }
                ft_memcpy(new_temp, temp, i);
                new_temp[i] = ' ';
                ft_memcpy(new_temp + i + 1, temp + i, len - i + 1);
                free(temp);
                temp = new_temp;
                len = new_len;
                i++; // Move index forward due to the inserted space
            }
            // Add space after operator if not present
            if (i + 1 < len && temp[i + 1] != ' ') 
            {
                new_len = len + 1;
                char *new_temp = malloc(new_len + 1);
                if (!new_temp)
                {
                    free(temp);
                    return 1;
                }
                ft_memcpy(new_temp, temp, i + 1);
                new_temp[i + 1] = ' ';
                ft_memcpy(new_temp + i + 2, temp + i + 1, len - i);
                free(temp);
                temp = new_temp;
                len = new_len;
            }
        }
        i++;
    }
    free(shell->name);
    shell->name = temp;
    return 0;
}

int split(t_minishell *shell)
{
    int i = 0;
    if (!*shell->name || !shell->name)
    {
        return 0;
    }
    while (shell->name[i])
    {
        if (shell->name[i] == 39 || shell->name[i] == '"')
        {
            if (closed_quotes(shell, shell->name[i]) == 1)
            {
                printf("Error: Unclosed quotes\n");
                return(1);
            }
        i = (handle_quote(shell,shell->name[i]) + i + 1);
        }
        if (shell->name[i] == '|' || shell->name[i] == '<' || shell->name[i] == '>')
        {
            if (handle_operation(shell) == 1)
                return 1;
            if (split_operation(shell, shell->name[i]) == 1)
                return 1;
        }
        i++;
    }
    if (split_space(shell) == 1)
        return 1;
    process_node_list(shell);
    return 0;
}

void process_node_list(t_minishell *shell)
{
    // t_node *head = create_node_list(shell->token_space);
    shell->token_list = create_node_list(shell->token_space);
    // if (head)
    // {
    //     t_node *current = head;
    //     while (current != NULL)
    //     {
    //         printf("%s", current->node);
    //         if (current->next != NULL)
    //             printf(" -> ");
    //         current = current->next;
    //     }
    //     printf(" -> NULL\n");
    //     current = head;
    //     while (current != NULL)
    //     {
    //         t_node *temp = current;
    //         current = current->next;
    //         free(temp->node);
    //         free(temp);
    //     }
    // }
    if (shell->token_list && shell->token_list->next == NULL && shell->token_list->node && 
    (shell->token_list->node[0] == '|' || shell->token_list->node[0] == '<' || shell->token_list->node[0] == '>'))
    {
        printf("minishell: syntax error near unexpected token `|'\n");
       //free_node_list(shell->token_list);  // Free the token list before exiting
        return;
    }
    t_node *temp = shell->token_list;
    while (temp->next)
    {
        temp = temp->next;
    }
    if ((ft_strcmp(temp->node,">") == 0 || ft_strcmp(temp->node,"<") == 0|| ft_strcmp(temp->node,"|") == 0 )
    && temp->next == NULL)
    {
        printf("syntax error near unexpected token\n");
        return;
    }

    int i = 0;
    while (shell->token_space[i])
    {
        free(shell->token_space[i]);
        i++;
    }
    free(shell->token_space);
    if(parsing(&shell) == 1)
        return ;
}
