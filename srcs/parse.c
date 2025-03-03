/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:24:49 by fghanem           #+#    #+#             */
/*   Updated: 2025/03/03 15:41:00 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

void    parsing(t_minishell **shell)
{
    t_node  *temp;
    t_cmd   *cmd;
    t_cmd   *cmd2;
    int     i;


    init_cmd(&cmd);
    if(!cmd)
    {
        perror("error allocate t_cmd");
        exit(1);
    }
    i = 0;
    temp = (*shell)->token_list;
    cmd2 = cmd;
    while (temp)
    {
        if (temp->next && ((ft_strcmp(temp->node , "<") == 0) && (ft_strcmp(temp->next->node , "<") != 0)))
        {
            // printf("ff\n");
            temp->cmd_type = TOKEN_REDIRECT_IN;
            cmd2->file_in = ft_strdup(temp->next->node);
            temp = temp->next;
        }
        else if (temp->next && ((ft_strcmp(temp->node , ">") == 0 ) && (ft_strcmp(temp->next->node , ">") != 0)))
        {
            temp->cmd_type = TOKEN_REDIRECT_OUT;
            cmd2->file_out = ft_strdup(temp->next->node);
            temp = temp->next;
        }
        else if (temp->next && temp->next->next && ((ft_strcmp(temp->node , ">") == 0) && (ft_strcmp(temp->next->node , ">") == 0)))
        {
            temp->cmd_type = TOKEN_APPEND;
            cmd2->file_out = ft_strdup(temp->next->next->node);
            temp = temp->next->next;
        }
        else if (temp->next && temp->next->next && ((ft_strcmp(temp->node , "<") == 0) && (ft_strcmp(temp->next->node , "<") == 0)))
        {
            temp->cmd_type = TOKEN_HEREDOC;
            cmd2->file_in = ft_strdup(temp->next->next->node);
            temp = temp->next->next;
        }
        else if (ft_strcmp(temp->node , "|") == 0 && temp->next)
        {
            temp->cmd_type = TOKEN_PIPE;
            if (cmd2)
            {
                cmd2->file_out = ft_strdup("PIPE");
                init_cmd(&cmd2->next);
                cmd2 = cmd2->next;
                i = 0;
            }
        }
        else if (temp->node)
        {
            temp->cmd_type = TOKEN_WORD;
            cmd2->args[i++] = ft_strdup(temp->node);
            cmd2->args[i] = NULL;
        }
        temp = temp->next;
    }
    (*shell)->cmd_list = &(cmd);
    print(shell);
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
            printf("args : %s\n", temp->args[i++]);
        if(temp->file_in)
            printf("file_in: %s\n", temp->file_in);
        if (temp->file_out)
            printf("file_out: %s\n", temp->file_out);
        if(temp->next)
            printf("next -> CMD \n\n");
        temp = temp->next;
    }
}

void    init_cmd(t_cmd **cmd)
{
    t_cmd   *temp;

    temp = malloc(sizeof(t_cmd));
    if(!temp)
    {
        perror("failed to allocate structer command");
        return ;
    }
    temp->file_in = NULL;
    temp->file_out = NULL;
    temp->args = (char **)malloc(sizeof(char *) * 100);
    if(!temp->args)
    {
        perror("failed to allocate arguments");
        free(temp);
        return ;
    }
    temp->next = NULL;
    (*cmd) = temp;
}

// void    define_cmds(t_minishell **shell)
// {
//     t_node  *temp;
//     t_cmd   **cmd;
//     int     i;

//     init_cmd(cmd);
//     i = 0;
//     temp = (*shell)->token_list;
//     while(temp)
//     {
//         while (temp->cmd_type != TOKEN_REDIRECT_IN && temp->next->cmd_type == TOKEN_WORD)
//         {
//             temp->cmd_type = COMMAND;
//             (*cmd)->args[i] = ft_strdup(temp->node);
//         }
//     }
// }
