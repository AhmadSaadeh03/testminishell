/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/04/09 13:37:28 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

int main(int arc, char **arv, char **envp)
{
    t_minishell *shell = NULL;
    t_env   *env_list;

    (void)arv;
    (void)arc;
    shell = init_shell(shell);
    if (!shell)
    {
        printf("ERROR:%s \n", "fail allocation of shell");
        exit(1);
    }
    env_list = NULL;
    env_list = copy_env_to_list(envp);
    while (1)
    {
        shell->name = readline("👾 Minihell> ");
        if(*(shell->name) == '\0')
        {
            free(shell->name);
            continue ;
        }
        add_history(shell->name);
        if (split(shell) == 1)
            free_and_exit(shell);
        expand(shell, env_list);
        free(shell->name);
    }
    free_and_exit(shell);
    return (0);
}
