/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:49:35 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/26 17:07:02 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executing(t_minishell *shell)
{
	t_cmd	*cmd;

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
		handle_signals(5);
		waitpid(pid, NULL, 0);
		if (s_signal == SIGINT)
			shell->last_exit = 130;
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
		if (handle_redirection(cmd, shell) == 1)
		{
			free_exit(shell);
			exit(1);
		}
		if (cmd->heredoc_flag == 1)
			heredoc_child(cmd, shell);
		free_exit(shell);
		exit(0);
	}
	else
	{
		handle_signals(5);
		waitpid(pid, NULL, 0);
		if (s_signal == SIGINT)
			shell->last_exit = 130;
	}
}

void	child_process(t_cmd *cmd, t_minishell *shell, int flag)
{
	if (handle_redirection(cmd, shell) == 1)
	{
		free_here_list(cmd->heredocs);
		free_exit(shell);
		exit(1);
	}
	if (s_signal == SIGINT)
	{
		free_exit(shell);
		exit(130);
	}
	if (cmd->heredoc_flag == 1)
		heredoc_child(cmd, shell);
	if (flag == 1)
		exec_builtin(shell, cmd->cmd_line);
	else
		get_path_cmd(shell, cmd->cmd_line);
	free_exit(shell);
	exit(0);
}
