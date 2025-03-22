/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:24:49 by fghanem           #+#    #+#             */
/*   Updated: 2025/03/22 14:15:10 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

// void    set_cmd(t_cmd *cmd, char *file_name, char *var, t_type type)
// {
//     if (type == TOKEN_REDIRECT_IN || type == TOKEN_HEREDOC)
//     {
//         cmd->redirect = ft_strdup(var);
//         cmd->file_in = ft_strdup(file_name);
//     }
//     else if (type == TOKEN_REDIRECT_OUT || type == TOKEN_APPEND)
//     {
//         if (type == TOKEN_APPEND)
//             cmd->append = 1;
//         cmd->redirect = ft_strdup(var);
//         cmd->file_out = ft_strdup(file_name);
//     }
// }

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

// void    fill_cmd(t_cmd  *cmd2, t_node *temp)
// {
//     int i;

//     i = 0;
//     while (temp)
//     {
//         if(temp->next && temp->cmd_type != TOKEN_PIPE && temp->cmd_type != TOKEN_ARG && temp->cmd_type != COMMAND)
//             set_cmd(cmd2, temp->next->node, temp->node, temp->cmd_type);
//         else if (temp->cmd_type == TOKEN_PIPE && temp->next)
//         {
//             if (cmd2)
//             {
//                 init_cmd(&cmd2->next);
//                 cmd2 = cmd2->next;
//                 cmd2->pipe = ft_strdup("|");
//                 if(!cmd2->pipe)
//                 return ;
//                 i = 0;
//             }
//         }
//         else if (temp->node && (temp->cmd_type == TOKEN_ARG || temp->cmd_type == COMMAND))
//         {
//             cmd2->args[i] = ft_strdup(temp->node);
//             if(!cmd2->args[i])
//             return ;
//             cmd2->args[++i] = NULL;
//         }
//         temp = temp->next;
//     }
// }

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
//      t_cmd   *temp;
//     int i =0;

//     temp = (*(*shell)->cmd_list);
//     while (temp)
//     {
//         i = 0;
//         while(temp->args[i])
//             printf("\nargs : %s\n", temp->args[i++]);
//         if(temp->file_in)
//             printf("file_in: %s\n", temp->file_in);
//         if (temp->file_out)
//             printf("file_out: %s\n", temp->file_out);
//         if(temp->next)
//             printf(" next -> CMD \n\n");
//         if (temp->append && ft_strcmp(temp->redirect ,">>") == 0)
//             printf("append : %s\n", temp->redirect);
//         // else if (!temp->append && ft_strcmp(temp->redirect ,"<<") == 0)
//         //     printf("here-document  : %s \n", temp->redirect);
//         if (temp->pipe)
//             printf("pipe : %s\n", temp->pipe);
//         temp = temp->next;
//     }
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
    // current = (*shell)->token_list;
    // while (current != NULL)
    // {
    //     t_node *temp = current;
    //     current = current->next;
    //     free(temp->node);
    //     free(temp);
    // }
}
