/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:42:20 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/10 14:04:24 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	init_pipe_data(t_pipes *pipe_data, int cmd_count)
{
	int	i;

	pipe_data->cmd_count = cmd_count;
	pipe_data->pid = malloc(sizeof(pid_t) * cmd_count);
	if (!pipe_data->pid)
		return (1);
	pipe_data->pipe_fd = malloc(sizeof(int) * 2 * (cmd_count - 1));
	if (!pipe_data->pipe_fd)
	{
		free(pipe_data->pid);
		return (1);
	}

	i = 0;
	while (i < (cmd_count - 1))
	{
		if (pipe(&pipe_data->pipe_fd[i * 2]) == -1)
		{
			perror("pipe");
			for (int j = 0; j < i; j++)
			{
				close(pipe_data->pipe_fd[j * 2]);
				close(pipe_data->pipe_fd[j * 2 + 1]);
			}
			free(pipe_data->pid);
			free(pipe_data->pipe_fd);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	free_pipe_data(t_pipes *pipe_data)
{
	int	i;

	for (i = 0; i < (pipe_data->cmd_count - 1) * 2; i++)
		close(pipe_data->pipe_fd[i]);
	free(pipe_data->pipe_fd);
	free(pipe_data->pid);
	pipe_data->pipe_fd = NULL;
	pipe_data->pid = NULL;
	pipe_data->cmd_count = 0;
}

void	preprocess_heredocs(t_cmd *cmd, t_minishell *shell)
{
	while (cmd)
	{
		if (cmd->heredoc_flag)
			exec_heredoc(cmd, shell);
		cmd = cmd->next;
	}
}

static void	wait_all_children(t_pipes *pipe_data)
{
	int	i;
	int	status;

	for (i = 0; i < pipe_data->cmd_count; i++)
		waitpid(pipe_data->pid[i], &status, 0);
}

void	exec_pipe(t_minishell *shell)
{
	t_pipes	pipe_data;
	t_cmd	*cmd_list;
	t_cmd	*cmd;
	int		i;

	cmd_list = *(shell->cmd_list);
	cmd = *(shell->cmd_list);
	preprocess_heredocs(cmd_list, shell);
	if (init_pipe_data(&pipe_data, cmd_count(cmd)) == 1)
		return ;
	i = 0;
	while (cmd)
	{
		pipe_data.pid[i] = fork();
		if (pipe_data.pid[i] == -1)
		{
			perror("fork");
			free_pipe_data(&pipe_data);
			free_exit(shell);
			return ;
		}
		if (pipe_data.pid[i] == 0)
		{
			if (i > 0)
				dup2(pipe_data.pipe_fd[(i - 1) * 2], STDIN_FILENO);
			if (i < pipe_data.cmd_count - 1)
				dup2(pipe_data.pipe_fd[i * 2 + 1], STDOUT_FILENO);
			close_fd(&pipe_data);
			if (cmd->redir_flag)
				handle_redirection(cmd, shell);
			if (cmd->cmd_line[0] && is_builtin(cmd->cmd_line[0]))
				exec_builtin(shell, cmd->cmd_line);
			else if (cmd->cmd_line[0])
				get_path_cmd(shell, cmd->cmd_line);
			free_pipe_data(&pipe_data);
			free_exit(shell);
			exit(0);
		}
		cmd = cmd->next;
		i++;
	}
	close_fd(&pipe_data);
	wait_all_children(&pipe_data);
	free(pipe_data.pid);
	free(pipe_data.pipe_fd);
}

void	close_fd(t_pipes *pipe_data)
{
	int	i = 0;
	
	while (i < (pipe_data->cmd_count - 1) * 2)
	{	
		close(pipe_data->pipe_fd[i]);
		i++;
	}
}

int	cmd_count(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

// int	open_pipes(t_pipes *pipe_data)
// {
// 	int	pipe_count;
// 	int	i;

// 	i = 0;
// 	pipe_count = pipe_data->cmd_count - 1;
// 	pipe_data->pipe_fd = malloc(sizeof(int) * 2 * (pipe_count));
// 	if (!pipe_data->pipe_fd)
// 		return (1);
// 	while (i < pipe_count)
// 	{
// 		if (pipe(pipe_data->pipe_fd + (i * 2)) == -1)
// 		{
// 			perror("pipe");
// 			free(pipe_data->pipe_fd);
// 			pipe_data->pipe_fd = NULL;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }



// void	run_cmd(t_minishell *shell, t_cmd *cmd, t_pipes *pipe_data, int i)
// {
// 	pipe_data->pid[i] = fork();
// 	if (pipe_data->pid[i] == -1)
// 	{
// 		perror("fork");
// 		free_minishell(shell);
// 		free(pipe_data->pid);
// 		free(pipe_data->pipe_fd);
// 		return ;
// 	}
// 	if (pipe_data->pid[i] == 0)
// 	{
// 		if (i > 0)
// 			dup2(pipe_data->pipe_fd[(i - 1) * 2], STDIN_FILENO);
// 		if (i < (pipe_data->cmd_count - 1))
// 			dup2(pipe_data->pipe_fd[i * 2 + 1], STDOUT_FILENO);
// 		close_fd(pipe_data);
// 		handle_pipe_cmd(shell, cmd);
// 		free_exit(shell);
// 		free(pipe_data->pid);
// 		exit(0);
// 	}
// }

// void	handle_pipe_cmd(t_minishell *shell, t_cmd *cmd)
// {
// 	if (is_builtin(cmd->cmd_line[0]) == 1)
// 	{
// 		if (cmd->heredoc_flag == 1 || cmd->redir_flag == 1)
// 		{
// 			handle_redirection(cmd);
// 			exec_builtin(shell, cmd->cmd_line);
// 		}
// 		else
// 			exec_builtin(shell, cmd->cmd_line);
// 	}
// 	else
// 	{
// 		if (cmd->heredoc_flag == 1 || cmd->redir_flag == 1)
// 		{
// 			handle_redirection(cmd);
// 			get_path_cmd(shell, cmd->cmd_line);
// 		}
// 		else
// 			get_path_cmd(shell, cmd->cmd_line);
// 	}
// }

// void	close_fd(t_pipes *pipe_data)
// {
// 	int	i;
// 	int	fd_count;

// 	if (!pipe_data->pipe_fd)
// 		return ;

// 	fd_count = (pipe_data->cmd_count - 1) * 2;
// 	i = 0;
// 	while (i < fd_count)
// 	{
// 		if (pipe_data->pipe_fd[i] >= 0)
// 			close(pipe_data->pipe_fd[i]);
// 		i++;
// 	}
// 	free(pipe_data->pipe_fd);
// 	pipe_data->pipe_fd = NULL;
// }

