/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:35:31 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/28 16:58:37 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    exec_builtin(t_minishell *shell, char **cmd_line)
{
    char    **envp;

    // if (!shell || !(*shell->cmd_list))
    //     return;
    envp = shell->envps;
    if (ft_strcmp(cmd_line[0], "echo") == 0)
        ft_echo(shell, cmd_line);
    else if (ft_strcmp(cmd_line[0], "cd") == 0)
        ft_cd(shell, cmd_line);
    else if (ft_strcmp(cmd_line[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(cmd_line[0], "env") == 0)
        ft_env(shell);
    else if (ft_strcmp(cmd_line[0], "export") == 0)
        ft_export(shell, cmd_line);
    else if (ft_strcmp(cmd_line[0], "unset") == 0)
        ft_unset(shell, cmd_line);
    else if (ft_strcmp(cmd_line[0], "exit") == 0)
        ft_exit(shell, cmd_line);
    else
        get_path_cmd(shell, cmd_line);
    // free_minishell(shell);
}

void    ft_cd(t_minishell *shell, char **cmd_line)
{
    char    *path;

    path = my_getenv((*shell->env_list), "HOME");
    if (cmd_line[1] == NULL)
    {
        if (chdir(path) != 0)
            perror("cd");
    }
    else
    {
        if (chdir(cmd_line[1]) != 0)
            perror("cd");
    }
    free(path);
}

void    ft_pwd()
{
    char *pwd = getcwd(NULL, 0);
    printf("%s\n", pwd);
}

void    ft_env(t_minishell *shell)
{
    print_env_list(shell->env_list);
}

void    ft_unset(t_minishell *shell, char **cmd_line)
{
    if (cmd_line[1])
        my_unsetenv(shell->env_list, cmd_line[1]);
    else
        return ;
}
