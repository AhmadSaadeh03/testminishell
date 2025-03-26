/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:16:34 by asaadeh           #+#    #+#             */
/*   Updated: 2025/03/26 14:42:06 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

int handle_operation(t_minishell *shell)
{
    int i = 0;
    int len = ft_strlen(shell->name);
    while (shell->name[i])
    {
        if ((i == 0 && (shell->name[i] == '|' || shell->name[i] == '>' || shell->name[i] == '<')) 
        || (i == len - 1 &&(shell->name[i] == '|' || shell->name[i] == '>' || shell->name[i] == '<')))
        {
            printf("minishell: syntax error near unexpected token `newline'\n");
            return 1;
        }
        if (shell->name[i] == '|' && shell->name[i + 1] == '|')
        {
            printf("syntax error near unexpected token '|'\n");
            return 1;
        }
        if (shell->name[i] == '>' && shell->name[i + 1] == '>' && shell->name[i + 2] == '>')
        {
            printf("syntax error near unexpected token 'append or herdoc'\n");
            return 1;
        }
         if (shell->name[i] == '<' && shell->name[i + 1] == '<' && shell->name[i + 2] == '<')
        {
            printf("syntax error near unexpected token 'append or herdoc'\n");
            return 1;
        }
        i++;
    }  
    return 0;
}
