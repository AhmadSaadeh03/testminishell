/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:12:34 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/22 17:21:09 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void ft_echo(t_minishell *shell, t_cmd *cmd)
{
    int i;
    int newline;
    int flag_arg;
    char    *exit;

    i = 1;
    newline = 1;
    (void)shell;
    if (cmd->cmd_line[i][0] == '-')
    {
        flag_arg = handle_echo_flag(cmd->cmd_line[i]);
        if (flag_arg)
        {
            newline = !newline;
            i++;
        }
    }
    exit = ft_itoa(shell->last_exit);
    {
        
	}
    while (cmd->cmd_line[i])
    {
        if (cmd->cmd_line[i][0] == '$' && cmd->cmd_line[i][1] == '?')
        {
            handle_exit_status(exit, cmd->cmd_line[i]);
            i++;
        }
        else
            printf("%s", cmd->cmd_line[i]);
        if (cmd->cmd_line[i + 1])
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
            if (arg[j] != 'n' && arg[j] != 'e' && arg[j] != 'E')
                return (0);
            j++;
        }
    }
    return (1);
}

void    handle_exit_status(char *exit,char *arg)
{
    char *suffix;
    char *joined;
    
    suffix = ft_strdup(arg + 2);
    joined = ft_strjoin(exit, suffix);
    printf("%s", joined);
    free(suffix);
    free(joined);
}
