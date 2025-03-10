/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:24:49 by fghanem           #+#    #+#             */
/*   Updated: 2025/03/10 13:19:33 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

void    init_cmd(t_cmd **cmd)
{
    t_cmd   *temp;

    temp = NULL;
    temp = malloc(sizeof(t_cmd));
    if(!temp)
    {
        perror("failed to allocate structer command");
        return ;
    }
    temp->file_in = NULL;
    temp->file_out = NULL;
    temp->args = NULL;
    temp->args = (char **)malloc(sizeof(char *) * 50);
    if(!temp->args)
    {
        perror("failed to allocate arguments");
        free(temp);
        return ;
    }
    temp->next = NULL;
    (*cmd) = temp;
}

void    set_cmd(t_cmd *cmd, char *file_name, int flag)
{
    if (flag == 0)
        cmd->file_in = ft_strdup(file_name);
    else
        cmd->file_out = ft_strdup(file_name);
}

void    parsing(t_minishell **shell)
{
    t_node  *temp;
    t_cmd   *cmd;
    t_cmd   *cmd2;
    int     i;

    init_cmd(&cmd);
    i = 0;
    temp = (*shell)->token_list;
    cmd2 = cmd;
    while (temp)
    {
        if (temp->next && temp->cmd_type == TOKEN_REDIRECT_IN)
            set_cmd(cmd2, temp->next->node, 0);
        else if (temp->next && temp->cmd_type == TOKEN_REDIRECT_OUT)
            set_cmd(cmd2, temp->next->node, 1);
        else if (temp->next && temp->cmd_type == TOKEN_APPEND)
            set_cmd(cmd2, temp->next->node, 1);
        else if (temp->next && temp->cmd_type == TOKEN_HEREDOC)
            set_cmd(cmd2, temp->next->node, 0);
        else if (temp->cmd_type == TOKEN_PIPE && temp->next)
        {
            if (cmd2)
            {
                init_cmd(&cmd2->next);
                cmd2 = cmd2->next;
                i = 0;
            }
        }
        else if (temp->node)
        {
            cmd2->args[i++] = ft_strdup(temp->node);
            cmd2->args[i] = NULL;
        }
        temp = temp->next;
    }
    (*shell)->cmd_list = &cmd;
    print(shell);
}

void    put_type(t_minishell **shell)
{
    t_node  *temp;

    temp = (*shell)->token_list;
    temp = fix_redirection(temp);
    while (temp)
    {
        if (temp->next && (ft_strcmp(temp->node , "<") == 0))
            temp->cmd_type = TOKEN_REDIRECT_IN;
        else if (temp->next && (ft_strcmp(temp->node , ">") == 0))
            temp->cmd_type = TOKEN_REDIRECT_OUT;
        else if (temp->next && (ft_strcmp(temp->node , ">>") == 0))
            temp->cmd_type = TOKEN_APPEND;
        else if (temp->next && (ft_strcmp(temp->node , "<<") == 0))
            temp->cmd_type = TOKEN_HEREDOC;
        else if (ft_strcmp(temp->node , "|") == 0 && temp->next)
            temp->cmd_type = TOKEN_PIPE;
        else
            temp->cmd_type = TOKEN_WORD;
        temp = temp->next;
    }
    prt_list(shell);
    parsing(shell);
}

void    print(t_minishell **shell)
{
    t_cmd   *temp;
    int i =0;
    
    temp = (*(*shell)->cmd_list);
    while (temp)
    {
        i = 0;
        while(temp->args[i])
            printf("\nargs : %s\n", temp->args[i++]);
        if(temp->file_in)
            printf("file_in: %s\n", temp->file_in);
        if (temp->file_out)
            printf("file_out: %s\n", temp->file_out);
        if(temp->next)
            printf("next -> CMD \n\n");
        temp = temp->next;
    }
    free(temp);
}

t_node  *fix_redirection(t_node *list)
{
    t_node  *temp;
    t_node  *to_free;

    temp = list;
    while(temp)
    {
        if (temp->next && ((ft_strcmp(temp->node , "<") == 0) && (ft_strcmp(temp->next->node , "<") == 0)))
        {
            to_free = temp->next;
            temp->next = temp->next->next;
            free_node(to_free);
            free(temp->node);
            temp->node = ft_strdup("<<");
            temp = temp->next;
        }
        if (temp->next && ((ft_strcmp(temp->node , ">") == 0) && (ft_strcmp(temp->next->node , ">") == 0)))
        {
            to_free = temp->next;
            temp->next = temp->next->next;
            free_node(to_free);
            free(temp->node);
            temp->node = ft_strdup(">>");
            temp = temp->next;
                
        }
        temp = temp->next;
    }
    return (list);
}

void free_node(t_node *to_free)
{
    free(to_free->node);
    free(to_free);
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
    // printf(" -> NULL\n");
    // current = (*shell)->token_list;
    // while (current != NULL)
    // {
    //     t_node *temp = current;
    //     current = current->next;
    //     free(temp->node);
    //     free(temp);
    // }
}

// void    def_cmd(t_minishell **shell)
// {
//     t_cmd   *cmd;
//     int     i;

//     i = 0;
//     cmd = (*(*shell)->cmd_list);
//     while(cmd)
//     {
//         while (cmd->args[i])
//         {
//             if (ft_strcmp(cmd->args, "ls"));
//         }
//     }
// }
