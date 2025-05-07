/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:38:28 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/07 16:25:15 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	external_cmd(t_minishell *shell, t_cmd *cmd)
{
	if ((cmd->heredoc_flag == 1 || cmd->redir_flag == 1))
		exec_red_cmd(cmd, shell, 0);
	else
	{
		get_path_cmd(shell, cmd->cmd_line);
	}
}

void	get_path_cmd(t_minishell *shell, char **args)
{
	char	*path_env;
	int		i;
	char	**path;
	char	*temp;
	char	*cmd_path;

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
	{
		execute_cmd(cmd_path, shell, shell->envps, args);
		free_array(shell->envps);
		free(cmd_path);
	}
	else if (!cmd_path && check_cmd_path(shell, args) == 0)
	{
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->last_exit = 127;
		free_array(shell->envps);
	}
	free_array(path);
}

void	execute_cmd(char *cmd_path, t_minishell *shell, char **envp,
		char **cmd_line)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if(execve(cmd_path, cmd_line, envp) == -1)
		{
			free_array(envp);
			ft_putstr_fd(cmd_line[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		free_exit(shell);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

// to handle /bin/ls

int	check_cmd_path(t_minishell *shell, char **cmd_line)
{
	if (ft_strchr(cmd_line[0], '/') != NULL)
	{
		execute_cmd(cmd_line[0], shell, shell->envps, cmd_line);
		return (1);
	}
	else
		return (0);
}
