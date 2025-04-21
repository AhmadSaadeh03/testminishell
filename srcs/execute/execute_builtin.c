/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:35:31 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/21 17:04:00 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    is_builtin(t_minishell *shell, char **envp)
{
    t_cmd   *cmd;

    cmd = *(shell->cmd_list); 
    if (ft_strcmp(cmd->cmd_line[0], "echo") == 0)
        ft_echo(shell, cmd);
    // else if (ft_strcmp(cmd->cmd_line[0], "cd") == 0)
    //     ft_cd(shell, cmd);
    else if (ft_strcmp(cmd->cmd_line[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(cmd->cmd_line[0], "env") == 0)
        ft_env(shell);
    else if (ft_strcmp(cmd->cmd_line[0], "export") == 0)
        ft_export(shell, cmd);
    else if (ft_strcmp(cmd->cmd_line[0], "unset") == 0)
        ft_unset(shell, cmd);
    // else if (ft_strcmp(cmd->cmd_line[0], "exit") == 0)
    //     ft_exit(shell, cmd);
    else
        get_path_cmd(shell, envp, cmd->cmd_line);
}
// void    ft_cd(t_minishell *shell, t_cmd *cmd)
// {
//     int i;

    
// }


void    ft_pwd()
{
    char *pwd = getcwd(NULL, 0);
    printf("%s\n", pwd);
}

void    ft_env(t_minishell *shell)
{
    print_env_list(shell->env_list);
}

void    ft_unset(t_minishell *shell, t_cmd *cmd)
{
    if (cmd->cmd_line[1])
        my_unsetenv(shell->env_list, cmd->cmd_line[1]);
    else
        return;
}
