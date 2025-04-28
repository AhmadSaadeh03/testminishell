/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:12:34 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/28 15:59:48 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void ft_echo(t_minishell *shell, char **cmd_line)
{
    int i;
    int newline;
    int flag_arg;
    char    *exit;

    i = 1;
    exit = NULL;
    newline = 1;
    if (cmd_line[i][0] == '-')
    {
        flag_arg = handle_echo_flag(cmd_line[i]);
        if (flag_arg)
        {
            newline = !newline;
            i++;
        }
    }
    while (cmd_line[i] != NULL)
    {
        if (cmd_line[i][0] == '$' && cmd_line[i][1] == '?')
        {
            exit = ft_itoa(shell->last_exit);
            if (!exit)
                return ;
            handle_exit_status(exit, cmd_line[i]);
            shell->last_exit = 0;
            free(exit);
            i++;
        }
        else if (cmd_line[i][0] == '$' && cmd_line[i][1] == '_')
        {
            printf("%s",shell->print_last_arg);
            //free(shell->last_arg);
        }
        else
            printf("%s", cmd_line[i]);
        if (cmd_line[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
}

int handle_echo_flag(char *arg)
{
    int j;

    j = 0;
    if (arg[j] == '-' && arg[j + 1] == 'n')
    {
        j++;
        while(arg[j])
        {
            if (arg[j] != 'n')
            {
                if (arg[j] == 'e' || arg[j] == 'E')
                    return (1);
                return(0);
            }
            j++;
        }
    }
    return (1);
}

void    handle_exit_status(char *exit, char *arg)
{
    char *suffix;
    char *joined;
    
    suffix = ft_strdup(arg + 2);
    joined = ft_strjoin(exit, suffix);
    printf("%s", joined);
    free(suffix);
    free(joined);
}
