/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:42:20 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/12 14:01:54 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	preprocess_heredocs(t_cmd *cmd, t_minishell *shell)
{
	while (cmd)
	{
		if (cmd->heredoc_flag)
			exec_heredoc(cmd, shell);
		cmd = cmd->next;
	}
}

void	wait_all_children(t_pipes *pipe_data)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipe_data->cmd_count)
	{
		waitpid(pipe_data->pid[i], &status, 0);
		i++;
	}
}

void	handle_child_process(t_minishell *shell, t_cmd *cmd, t_pipes *pipe_data, int i)
{
	if (cmd->heredoc_flag == 1)
		heredoc_child(cmd, shell);
	else if (i > 0)
		dup2(pipe_data->pipe_fd[(i - 1) * 2], STDIN_FILENO);
	if (i < pipe_data->cmd_count - 1)
		dup2(pipe_data->pipe_fd[i * 2 + 1], STDOUT_FILENO);
	close_fd(pipe_data);
	if (cmd->redir_flag)
		handle_redirection(cmd, shell);
	if (cmd->cmd_line[0] && is_builtin(cmd->cmd_line[0]))
		exec_builtin(shell, cmd->cmd_line);
	else if (cmd->cmd_line[0])
		get_path_cmd(shell, cmd->cmd_line);
	free_pipe_data(pipe_data);
	free_exit(shell);
	exit(0);
}

int	create_child_processes(t_minishell *shell, t_pipes *pipe_data, t_cmd *cmd)
{
	int	i = 0;

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
		cmd = cmd->next;
		i++;
	}
	return (0);
}

void	exec_pipe(t_minishell *shell)
{
	t_pipes	pipe_data;
	t_cmd	*cmd;

	cmd = *(shell->cmd_list);
	preprocess_heredocs(cmd, shell);
	if (init_pipe_data(&pipe_data, cmd_count(cmd)) == 1)
		return ;
	if (create_child_processes(shell, &pipe_data, cmd) == 1)
		return ;
	close_fd(&pipe_data);
	wait_all_children(&pipe_data);
	free(pipe_data.pid);
	free(pipe_data.pipe_fd);
}
