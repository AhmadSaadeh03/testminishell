/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/04/14 15:40:16 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int arc, char **arv, char **envp)
{
    t_minishell *shell = NULL ;
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
        shell->name = readline("👾Minihell> ");
        if(shell->name)
        {
            add_history(shell->name);
            split(shell);
            expand(shell, &env_list);
            //free(shell->name);
            add_history(shell->name);
            //add_history(shell->name);
        }
        else
            exit(1);
    }
    free_and_exit(shell);
    return (0);
}
