/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/04/21 19:28:46 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int arc, char **arv, char **envp)
{
    t_minishell *shell = NULL;

    (void)arv;
    (void)arc;
    shell = init_shell(shell, envp);
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
        split(shell);
        //print(shell->cmd_list);
            //free_minishell(shell);
        is_builtin(shell, shell->envps);
            // get_path_cmd(shell, shell->envps, (*shell->cmd_list)->cmd_line);
        // free_minishell(shell);
    }
    free_and_exit(shell);
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
