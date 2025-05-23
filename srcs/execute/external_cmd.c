/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:38:28 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/24 15:10:55 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	external_cmd(t_minishell *shell, t_cmd *cmd)
{
	if ((cmd->heredoc_flag == 1 || cmd->redir_flag == 1))
		exec_red_cmd(cmd, shell, 0);
	else
		get_path_cmd(shell, cmd->cmd_line);
}

void	get_path_cmd(t_minishell *shell, char **args)
{
	char	*path_env;
	int		i;
	char	**path;
	char	*temp;
	char	*cmd_path;

	if (ft_strchr(args[0], '.') != NULL || ft_strchr(args[0], '/') != NULL)
	{
		check_cmd_path(shell, args);
		return ;
	}
	cmd_path = NULL;
	path_env = my_getenv((*shell->env_list), "PATH");
	if (!path_env)
	{
		print_error(": No such file or directory\n", args[0]);
		shell->last_exit = 127;
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
	free_array(path);
	if (!cmd_path)
	{
		print_error(": command not found\n", args[0]);
		free_array(shell->envps);
		shell->last_exit = 127;
		return ;
	}
	else
	{
		execute_cmd(cmd_path, shell, shell->envps, args);
		free_array(shell->envps);
		free(cmd_path);
	}
}

void	execute_cmd(char *cmd_path, t_minishell *shell, char **envp,
		char **cmd_line)
{
	pid_t	pid;
	int		status;

	pid = fork();
	handle_signals(1);
	//s_signal = SIGQUIT;
	if (pid == 0) //child
	{
		//handle_signals(1);
		if (execve(cmd_path, cmd_line, envp) == -1)
		{
			free_array(envp);
			free(cmd_path);
			free_exit(shell);
			shell->last_exit = 127;
			exit(1);
		}
		free_exit(shell);
		exit(0);
	}
	// else//parent
	// {
	handle_signals(2);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			shell->last_exit = s_signal + 128;
		else if (WTERMSIG(status) == SIGQUIT)
			shell->last_exit = s_signal + 128;
	}
	else if (WIFEXITED(status))
		shell->last_exit = WEXITSTATUS(status);
	// }
}

int	check_cmd_path(t_minishell *shell, char **cmd_line)
{
	struct stat	path_stat;

	if (stat(cmd_line[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		print_error(": is a directory\n", cmd_line[0]);
		shell->last_exit = 126;
		return (0);
	}
	if (access(cmd_line[0], X_OK) != 0)
	{
		print_error(": permission denied\n", cmd_line[0]);
		shell->last_exit = 126;
		return (0);
	}
	execute_cmd(cmd_line[0], shell, shell->envps, cmd_line);
	free_array(shell->envps);
	return (1);
}
