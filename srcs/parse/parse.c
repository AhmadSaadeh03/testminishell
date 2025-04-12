/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:24:49 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/10 18:37:54 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishill.h"

void    define_cmd(t_minishell **shell)
{
    t_node  *temp;

    temp = (*shell)->token_list;
    temp->cmd_type = COMMAND;
    temp = temp->next;
    while (temp)
    {
        if (temp->cmd_type == TOKEN_PIPE && temp->next)
        {
            temp->next->cmd_type = COMMAND;
            temp = temp->next;
        }
        temp = temp->next;
    }
}

int    parsing(t_minishell **shell)
{
    if (put_type(shell) == 1)
        return (1);
    define_cmd(shell);
    print(shell);
    return(0);
}

int    put_type(t_minishell **shell)
{
    t_node  *temp;

    temp = (*shell)->token_list;
    temp = fix_redirection(temp);
    if (!temp)
        return (1);
    while (temp)
    {
        if (temp->next && (ft_strcmp(temp->node , "<") == 0))
        {
            temp->cmd_type = TOKEN_REDIRECT_IN;
            temp->next->cmd_type = FILEIN;
            temp = temp->next;
        }
        else if (temp->next && (ft_strcmp(temp->node , ">") == 0))
        {
            temp->cmd_type = TOKEN_REDIRECT_OUT;
            temp->next->cmd_type = FILEOUT;
            temp = temp->next;
        }
        else if (temp->next && (ft_strcmp(temp->node , ">>") == 0))
        {
            temp->cmd_type = TOKEN_APPEND;
            temp->next->cmd_type = FILEOUT;
            temp = temp->next;
        }
        else if (temp->next && (ft_strcmp(temp->node , "<<") == 0))
        {
            temp->cmd_type = TOKEN_HEREDOC;
            temp->next->cmd_type = FILEIN;
            temp = temp->next;
        }
        else if (ft_strcmp(temp->node , "|") == 0 && temp->next)
            temp->cmd_type = TOKEN_PIPE;
        else
            temp->cmd_type = TOKEN_ARG;
        temp = temp->next;
    }
    return (0);
}

void    print(t_minishell **shell)
{
    printf("\n **********cmd*********\n");
    t_node  *tmp = (*shell)->token_list;
    while (tmp)
    {
        if(tmp->cmd_type == COMMAND)
            printf("cmd : %s \n", tmp->node);
        if(tmp->cmd_type == TOKEN_ARG)
            printf("ARG : %s \n", tmp->node);
        if(tmp->cmd_type == TOKEN_APPEND)
            printf("APPEND : %s \n", tmp->node);
        if(tmp->cmd_type == TOKEN_HEREDOC)
            printf("HERE-DOC : %s \n", tmp->node);
        if(tmp->cmd_type == FILEIN)
            printf("FILEIN : %s \n", tmp->node);
        if(tmp->cmd_type == FILEOUT)
            printf("FILEOUT : %s \n", tmp->node);
        if(tmp->cmd_type == TOKEN_PIPE)
            printf("PIPE : %s \n", tmp->node);
        tmp = tmp->next;
    }
}

t_node  *fix_redirection(t_node *list)
{
    t_node  *temp;
    t_node  *to_free;

    temp = list;
    while(temp)
    {
        if (temp->next && temp->next->next && ((ft_strcmp(temp->node , "<") == 0) && (ft_strcmp(temp->next->node , "<") == 0)))
        {
            to_free = temp->next;
            temp->next = temp->next->next;
            free_node(to_free);
            free(temp->node);
            temp->node = ft_strdup("<<");
            if (!temp->node)
                return (NULL);
            temp = temp->next;
        }
        if (temp->next && temp->next->next && ((ft_strcmp(temp->node , ">") == 0) && (ft_strcmp(temp->next->node , ">") == 0)))
        {
            to_free = temp->next;
            temp->next = temp->next->next;
            free_node(to_free);
            free(temp->node);
            temp->node = ft_strdup(">>");
            if (!temp->node)
                return (NULL);
            temp = temp->next;
        }
        temp = temp->next;
    }
    return (list);
}

//////////////////////////// delete 
void    prt_list(t_minishell **shell)
{
    t_node  *current = NULL;
    
    printf("\n%s\n", "----------after-------------");
    current = (*shell)->token_list;
    while (current != NULL)
    {
        printf("%s", current->node);
        if (current->next != NULL)
            printf(" -> ");
        current = current->next;
    }
    printf(" -> NULL\n");
}
