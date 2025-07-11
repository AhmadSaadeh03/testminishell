/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:38:28 by fghanem           #+#    #+#             */
/*   Updated: 2025/06/01 13:14:53 by asaadeh          ###   ########.fr       */
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

char	*find_path(char **path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*cmd_path;
	char	*path_env;

	cmd_path = NULL;
	i = 0;
	while (path[i])
	{
		path_env = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(path_env, cmd);
		free(path_env);
		if (access(tmp, X_OK) == 0)
		{
			cmd_path = ft_strdup(tmp);
			free(tmp);
			break ;
		}
		free(tmp);
		i++;
	}
	return (cmd_path);
}

void	get_path_cmd(t_minishell *shell, char **args)
{
	char	**path;
	char	*cmd_path;

	shell->envps = copy_env_list_to_array((*shell->env_list));
	if (!shell->envps)
		return ;
	if (ft_strchr(args[0], '/') != NULL)
	{
		if (!check_cmd_path(shell, args))
			free_array(shell->envps);
		return ;
	}
	path = get_path_array(shell, args[0]);
	if (!path)
	{
		free_array(shell->envps);
		return ;
	}
	cmd_path = find_path(path, args[0]);
	free_array(path);
	if (!prepare_env_and_check(shell, cmd_path, args[0]))
		return ;
	execute_cmd(cmd_path, shell, shell->envps, args);
	free_array(shell->envps);
	free(cmd_path);
}

void	execute_cmd(char *cmd_path, t_minishell *shell, char **envp,
		char **cmd_line)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		handle_signals(1);
		if (execve(cmd_path, cmd_line, envp) == -1)
		{
			free_array(envp);
			free(cmd_path);
			free_exit(shell);
			exit(127);
		}
		free_exit(shell);
		exit(0);
	}
	signal(SIGPIPE, SIG_IGN);
	handle_signals(2);
	waitpid(pid, &status, 0);
	handle_exit_status(shell, status);
	if (g_signal == SIGINT || g_signal == SIGPIPE)
		write(1, "\n", 1);
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
	if (access(cmd_line[0], F_OK) != 0)
	{
		print_error(": command not found\n", cmd_line[0]);
		shell->last_exit = 127;
		return (0);
	}
	else if (access(cmd_line[0], X_OK) != 0)
	{
		print_error(": permission denied\n", cmd_line[0]);
		shell->last_exit = 126;
		return (0);
	}
	execute_cmd(cmd_line[0], shell, shell->envps, cmd_line);
	free_array(shell->envps);
	return (1);
}
