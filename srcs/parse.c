/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:24:49 by fghanem           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/03 15:41:00 by fghanem          ###   ########.fr       */
=======
/*   Updated: 2025/03/08 14:29:57 by fghanem          ###   ########.fr       */
>>>>>>> f26bb66 (new)
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

<<<<<<< HEAD
=======
void    set_cmd(t_cmd *cmd, char *file_name, int flag)
{
    if (flag == 0)
        cmd->file_in = ft_strdup(file_name);
    else
        cmd->file_out = ft_strdup(file_name);
}

>>>>>>> f26bb66 (new)
void    parsing(t_minishell **shell)
{
    t_node  *temp;
    t_cmd   *cmd;
    t_cmd   *cmd2;
    int     i;

<<<<<<< HEAD

    init_cmd(&cmd);
    if(!cmd)
    {
        perror("error allocate t_cmd");
        exit(1);
    }
=======
    init_cmd(&cmd);
>>>>>>> f26bb66 (new)
    i = 0;
    temp = (*shell)->token_list;
    cmd2 = cmd;
    while (temp)
    {
<<<<<<< HEAD
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
=======
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
>>>>>>> f26bb66 (new)
                init_cmd(&cmd2->next);
                cmd2 = cmd2->next;
                i = 0;
            }
        }
        else if (temp->node)
        {
<<<<<<< HEAD
            temp->cmd_type = TOKEN_WORD;
=======
>>>>>>> f26bb66 (new)
            cmd2->args[i++] = ft_strdup(temp->node);
            cmd2->args[i] = NULL;
        }
        temp = temp->next;
    }
<<<<<<< HEAD
    (*shell)->cmd_list = &(cmd);
    print(shell);
}

=======
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

>>>>>>> f26bb66 (new)
void    print(t_minishell **shell)
{
    t_cmd   *temp;
    int i =0;
    
    temp = (*(*shell)->cmd_list);
    while (temp)
    {
        i = 0;
        while(temp->args[i])
<<<<<<< HEAD
            printf("args : %s\n", temp->args[i++]);
=======
            printf("\nargs : %s\n", temp->args[i++]);
>>>>>>> f26bb66 (new)
        if(temp->file_in)
            printf("file_in: %s\n", temp->file_in);
        if (temp->file_out)
            printf("file_out: %s\n", temp->file_out);
        if(temp->next)
            printf("next -> CMD \n\n");
        temp = temp->next;
    }
<<<<<<< HEAD
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
=======
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
>>>>>>> f26bb66 (new)
