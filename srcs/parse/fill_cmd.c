/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:31:06 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/12 15:55:09 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishill.h"

void    set_cmd(t_cmd *cmd, char *file_name, char *var, t_type type)
{
    if (type == TOKEN_REDIRECT_IN || type == TOKEN_HEREDOC)
    {
        if (type == TOKEN_HEREDOC && ft_strcmp(var, "<<") == 0)
        {
            cmd->limiter = ft_strdup(file_name);
            cmd->redirect = ft_strdup(var);
        }
        else
        {
            cmd->redirect = ft_strdup(var);
            cmd->file_in = ft_strdup(file_name);
        }
    }
    else if (type == TOKEN_REDIRECT_OUT || type == TOKEN_APPEND)
    {
        if (type == TOKEN_APPEND)
            cmd->append = 1;
        cmd->redirect = ft_strdup(var);
        cmd->file_out = ft_strdup(file_name);
    }
}


void    fill_cmd(t_cmd  *cmd2, t_node *temp)
{
    int i;

    i = 0;
    while (temp)
    {
        if (temp->next && (temp->cmd_type == TOKEN_HEREDOC || temp->cmd_type == TOKEN_APPEND || temp->cmd_type == TOKEN_REDIRECT_IN || temp->cmd_type == TOKEN_REDIRECT_OUT) )
        {
            set_cmd(cmd2, temp->next->node, temp->node, temp->cmd_type);
            temp = temp->next;
        }
        else if (temp->cmd_type == TOKEN_PIPE && temp->next)
        {
            if (cmd2)
            {
                init_cmd(&cmd2->next);
                cmd2 = cmd2->next;
                cmd2->pipe = ft_strdup("|");
                if(!cmd2->pipe)
                    return ;
                i = 0;
            }
        }
        else if (temp->node && (temp->cmd_type == TOKEN_ARG || temp->cmd_type == COMMAND))
        {
            cmd2->cmd_line[i] = ft_strdup(temp->node);
            if(!cmd2->cmd_line[i])
                return ;
            cmd2->cmd_line[++i] = NULL;
        }
        temp = temp->next;
    }
}

void    cmd_filling(t_minishell **shell)
{
    t_cmd   *cmd;
    t_node  *temp;

    init_cmd(&cmd);
    if(!cmd)
        return ;
    temp = (*shell)->token_list;
    
    fill_cmd(cmd, temp);
    (*shell)->cmd_list = &cmd;
    free_tokens((*shell)->token_list);
    handle_redirection(shell);
}
