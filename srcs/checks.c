/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:30:05 by fghanem           #+#    #+#             */
/*   Updated: 2025/03/03 17:10:14 by asaadeh          ###   ########.fr       */
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
// int qoutes_handling(t_minishell *shell,char qoute)
// {
//     int i = 0;
//     int j = 0;
//     int flag = 0;
//     char *str;

//     str = (char *)malloc(sizeof(char) * (ft_strlen(shell->name) + 1));
//     if (!str)
//         return 0; // Return failure if memory allocation fails
//     while (shell->name[i])
//     {
//         if (shell->name[i] == qoute)
//         {
//             // Toggle the flag when encountering a quote
//             flag = !flag;
//         }     
//         if (flag)
//         {
//             str[j] = shell->name[i];
//             j++;
//         }     
//         i++;
//     }
//     str[j] = '"';
//     str[j+1] = '\0';
//     shell->token_type->quoted = str;
//     return 1;
// }