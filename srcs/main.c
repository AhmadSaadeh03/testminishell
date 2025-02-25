/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/02/25 11:58:09 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

int main(void)
{
    t_minishell shell;

    while (1)
    {
        shell.name = readline("minihell > ");
        if (shell.name == NULL) 
        {
            break;
        }
        add_history(shell.name);
        split(&shell);
        if (!&split_space)
                return 1;
        free(shell.name);
    }
    return 0;
}