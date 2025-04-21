/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:35:31 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/21 14:30:34 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int is_builtin(t_minishell *shell, char **envp)
// {
//     t_cmd   *cmd;

//     cmd = *(shell->cmd_list); 
//     if (ft_strcmp(cmd->cmd_line[0], "echo") == 0)
//         ft_echo(shell, cmd);
//     else if (ft_strcmp(cmd->cmd_line[0], "cd") == 0)
//         ft_cd(shell, cmd);
//     else if (ft_strcmp(cmd->cmd_line[0], "pwd") == 0)
//         ft_pwd();
//     else if (ft_strcmp(cmd->cmd_line[0], "env") == 0)
//         ft_env();
//     else if (ft_strcmp(cmd->cmd_line[0], "export") == 0)
//         ft_export(shell, cmd);
//     else if (ft_strcmp(cmd->cmd_line[0], "unset") == 0)
//         ft_unset(shell, cmd);
//     else if (ft_strcmp(cmd->cmd_line[0], "exit") == 0)
//         ft_exit(shell, cmd);
//     else
//         get_path_cmd(shell, envp, cmd->cmd_line);
// }

// void    ft_echo(t_minishell *shell, t_cmd *cmd)
// {
//     int i;

//     i = 0;
//     while (cmd->cmd_line[i])
//     {
//         if (ft_strcmp(cmd->cmd_line[i], "echo") == 0 && ft_strcmp(cmd->cmd_line[i + 1] , "-n") == 0)
//         {
//             i++;
//             while (cmd->cmd_line[i])
//                 printf("%s", )
//         }
//     }
// }