/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:38:28 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/28 15:50:26 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    get_path_cmd(t_minishell *shell, char **args)
{
    char    *path_env;
    int     i;
    char    **path;
    char    *temp;
    char    *cmd_path;

    cmd_path = NULL;
    path_env = my_getenv((*shell->env_list), "PATH");
    if (!path_env)
    {
        ft_putstr_fd("bash: ls: No such file or directory\n", 2);
        return ;
    }
    path = ft_split(path_env, ':');
    i = 0;
    while (path[i])
    {
        path_env = ft_strjoin(path[i], "/");
        temp = ft_strjoin(path_env, args[0]);
        free(path_env);
        if (access(temp, X_OK) == 0)
        {
            cmd_path = ft_strdup(temp);
            free(temp);
            break ;
        }
        free(temp);
        i++;
    }
	shell->envps = copy_env_list_to_array((*shell->env_list));
    if (!shell->envps)
        return ;
    if (cmd_path)
        execute_cmd(cmd_path, shell, shell->envps, args);
    else
    {
        free_array(shell->envps);
        ft_putstr_fd(args[0], 2);
        ft_putstr_fd(": command not found\n",2);
        shell->last_exit = 127;
    }
}

void    execute_cmd(char *cmd_path, t_minishell *shell, char **envp, char **cmd_line)
{
    pid_t   pid;
    t_env   *env_list;

    pid = fork();
    env_list = (*shell->env_list);
    if (pid == 0)
    {
        if (execve(cmd_path, cmd_line, envp) == -1)
        {
            perror("Execve");
            shell->last_exit = 127;
            // exit(shell->last_exit);
            // free_and_exit(shell);
        }
    }
    else
        waitpid(pid, NULL, 0);
}
