/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:42:20 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/31 12:53:03 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	preprocess_heredocs(t_cmd *cmd, t_minishell *shell)
{
	while (cmd)
	{
		if (cmd->heredoc_flag)
		{
			exec_heredoc_pipe(cmd, shell);
			if (g_signal == SIGINT)
				return (2);
		}
		cmd = cmd->next;
	}
	return (0);
}

int	wait_all_children(t_pipes *pipe_data, t_minishell *shell)
{
	int	i;
	int	status;

	int	last_status;
	(void)shell;
	i = 0;
	while (i < pipe_data->cmd_count)
	{
		waitpid(pipe_data->pid[i], &status, 0);
		last_status = status;
		i++;
	}
	free(pipe_data->pid);
	pipe_data = NULL;
	return (last_status);
}

void	handle_child_process(t_minishell *shell, t_cmd *cmd, t_pipes *pipe_data,
		int i)
{
	int	temp;

	if (cmd->heredoc_flag == 1)
		heredoc_child(cmd, shell);
	else if (i > 0)
		dup2(pipe_data->pipe_fd[(i - 1) * 2], STDIN_FILENO);
	if (i < pipe_data->cmd_count - 1)
		dup2(pipe_data->pipe_fd[i * 2 + 1], STDOUT_FILENO);
	close_fd(pipe_data);
	if (cmd->redir_flag)
		handle_redirection(cmd, shell);
	free(pipe_data->pid);
	if (cmd->cmd_line[0] && is_builtin(cmd->cmd_line[0]))
		exec_builtin(shell, cmd->cmd_line);
	else if (cmd->cmd_line[0])
		get_path_cmd(shell, cmd->cmd_line);
	temp = shell->last_exit;
	free_exit(shell);
	exit(temp);
}

int	create_child_processes(t_minishell *shell, t_pipes *pipe_data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		pipe_data->pid[i] = fork();
		if (pipe_data->pid[i] == -1)
		{
			perror("fork");
			free_pipe_data(pipe_data);
			free_exit(shell);
			return (1);
		}
		if (pipe_data->pid[i] == 0)
			handle_child_process(shell, cmd, pipe_data, i);
		handle_signals(1);
		cmd = cmd->next;
		i++;
	}
	return (0);
}

void	exec_pipe(t_minishell *shell)
{
	t_pipes	pipe_data;
	int		status;
	t_cmd	*cmd;

	cmd = *(shell->cmd_list);
	if (preprocess_heredocs(cmd, shell) == 2)
		return ;
	if (init_pipe_data(&pipe_data, cmd_count(cmd)) == 1)
		return ;
	if (create_child_processes(shell, &pipe_data, cmd) == 1)
	{
		free_pipe_data(&pipe_data);
		return ;
	}
	close_fd(&pipe_data);
	status = wait_all_children(&pipe_data, shell);
	handle_exit_status(shell, status);
}
