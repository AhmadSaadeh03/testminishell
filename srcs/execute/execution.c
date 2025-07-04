/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:49:35 by fghanem           #+#    #+#             */
/*   Updated: 2025/06/01 12:25:08 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executing(t_minishell *shell)
{
	t_cmd	*cmd;

	g_signal = 0;
	cmd = *(shell->cmd_list);
	if (cmd && cmd->next)
		exec_pipe(shell);
	else
		execute_one_cmd(shell, cmd);
}

void	execute_one_cmd(t_minishell *shell, t_cmd *cmd)
{
	if ((cmd->heredoc_flag == 1 || cmd->redir_flag == 1)
		&& cmd->cmd_line[0] == NULL)
		exec_red_only(cmd, shell);
	else if (is_builtin(cmd->cmd_line[0]) == 1)
	{
		if (cmd->heredoc_flag == 1 || cmd->redir_flag == 1)
			exec_red_cmd(cmd, shell, 1);
		else
			exec_builtin(shell, cmd->cmd_line);
	}
	else
		external_cmd(shell, cmd);
}

void	exec_red_cmd(t_cmd *cmd, t_minishell *shell, int flag)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		child_process(cmd, shell, flag);
	else
	{
		handle_signals(2);
		waitpid(pid, NULL, 0);
	}
}

void	exec_red_only(t_cmd *cmd, t_minishell *shell)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (cmd->heredoc_flag == 1)
		{
			exec_heredoc(cmd, shell);
			heredoc_child(cmd, shell);
		}
		if (handle_redirection(cmd, shell) == 1)
		{
			free_exit(shell);
			exit(0);
		}
		free_exit(shell);
		exit(0);
	}
	handle_signals(2);
	waitpid(pid, NULL, 0);
	if (g_signal == SIGINT)
		shell->last_exit = g_signal + 128;
}

void	child_process(t_cmd *cmd, t_minishell *shell, int flag)
{
	if (cmd->heredoc_flag == 1)
	{
		exec_heredoc(cmd, shell);
		heredoc_child(cmd, shell);
	}
	if (handle_redirection(cmd, shell) == 1)
	{
		free_exit(shell);
		exit(0);
	}
	if (g_signal == SIGINT)
	{
		free_exit(shell);
		exit(130);
	}
	if (flag == 1)
		exec_builtin(shell, cmd->cmd_line);
	else
		get_path_cmd(shell, cmd->cmd_line);
	free_exit(shell);
	exit(0);
}
