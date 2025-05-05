/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/05 17:27:11 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_cmd_Aaa(t_cmd *cmd)
{
    t_cmd *temp;

    while (cmd)
    {
        temp = cmd;
        cmd = cmd->next;

        if (temp->cmd_line)
        {
            free_array(temp->cmd_line);
            free(temp->cmd_line);
        }
        // if (temp->redirect)
        //     free(temp->redirect);
        free_here_list(temp->heredocs);
        free(temp);
    }
}

void    free_here_list(t_here *heredocs)
{
    t_here *tmp;

    if (!heredocs)
    {
        return ;
    }
	while (heredocs)
	{
		tmp = heredocs->next;
        if(heredocs->limt)
            free(heredocs->limt);
		if(heredocs->content)
            free(heredocs->content);
		free(heredocs);
		heredocs = tmp;
	}
}

int main(int arc, char **arv, char **envp)
{
    t_minishell *shell;

    (void)arv;
    (void)arc;
    shell = init_shell(envp);
    if (!shell)
    {
        printf("ERROR:%s \n", "fail allocation of shell");
        exit(1);
    }
    while (1)
    {
        shell->name = readline("👾Minihell> ");
        // if (!shell->name)
        //     free_and_exit(shell);
        if (shell->name[0] == '\0' || is_all_whitespace(shell->name))
        {
            free(shell->name);
            continue;
        }
        add_history(shell->name);
        if (split(shell) == 1)
        {
            free(shell->name);
            continue ;
        }
        executing(shell);
        // free_start(shell);
    }
    free(shell);
    // create_free_env_list(*(shell->env_list));
    //free_cmd_Aaa(*shell->cmd_list);
    // free(shell->last_arg);
    //     }
    // free_and_exit(&shell);
    free_minishell(shell);
    return (0);
}

int is_all_whitespace(const char *str)
{
    while (*str)
    {
        if (!ft_isspace(*str))
            return 0;
        str++;
    }
    return 1;
}

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n'
        || c == '\v' || c == '\f' || c == '\r');
}

// void    new_prompt(t_minishell *shell)
// {
//     if (*(shell->cmd_list))
//         free_cmd(*(shell->cmd_list));
//     *(shell->cmd_list) = NULL;
// }

void print_cmd_list(t_cmd *head)
{
    int i = 0;
    while (head)
    {
        printf("------ Command #%d ------\n", i);
        
        if (head->cmd_line)
        {
            printf("Command Line: ");
            for (int j = 0; head->cmd_line[j]; j++)
                printf("'%s' ", head->cmd_line[j]);
            printf("\n");
        }
        else
            printf("Command Line: (null)\n");

        printf("heredoc_flag: %d\n", head->heredoc_flag);
        printf("redir_flag: %d\n", head->redir_flag);

        // You can add more info if needed, for example:
        // print_redirects(head->redirect);
        // print_heredocs(head->heredocs);

        head = head->next;
        i++;
    }
}