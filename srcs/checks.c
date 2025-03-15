/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:30:05 by fghanem           #+#    #+#             */
/*   Updated: 2025/03/15 15:47:06 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"
        
int closed_quotes(t_minishell *shell, char qoute) // this function to check that the qoutes are closed even number
{
    int i;
    int c;

    i = 0;
    c = 0;
    while (shell->name[i])
    {
        if (shell->name[i] == qoute)
            c++;
        i++;
    }
    if(c % 2 == 0)
        return(0);
    return(1);
}

int handle_quote(t_minishell *shell, char operator)
{
    int i = 0;
    int c = 0;
    int inside_quotes = 0;

    while(shell->name[i])
    {
        if (shell->name[i] == operator && !inside_quotes)
            inside_quotes = 1;
        else if (shell->name[i] == operator && inside_quotes)
        {
            inside_quotes = 0;
        }
        else if (inside_quotes)
            c++;
        i++;
    }
    printf("\n%d\n", c);
    return (c);
}