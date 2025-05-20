/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoom <fatoom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:49:35 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/20 17:12:50 by fatoom           ###   ########.fr       */
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

void	exec_red_cmd(t_cmd *cmd, t_minishell *shell, int fl)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		//handle_signals(1);
		if (handle_redirection(cmd, shell) == 1)
		{
			free_here_list(cmd->heredocs);
			free_exit(shell);
			exit(1);
		}
		if (cmd->heredoc_flag == 1)
			heredoc_child(cmd, shell);
		if (fl == 1)
			exec_builtin(shell, cmd->cmd_line);
		else
			get_path_cmd(shell, cmd->cmd_line);
		free_exit(shell);
		exit(0);
	}
	else
	{
		//handle_signals(1);
		waitpid(pid, NULL, 0);
	}
}

void	exec_red_only(t_cmd *cmd, t_minishell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
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
		waitpid(pid, NULL, 0);
}

void	heredoc_child(t_cmd *cmd, t_minishell *shell)//
{
	t_here *last;
	int		fd[2];

	if (pipe(fd) == -1)
		return ;
	//handle_signals(5);
	last = cmd->heredocs;
	while (last->next)
		last = last->next;
	if (last && last->content)
	{
		handle_signals(5);
		if (ft_strchr(last->content, '$'))
		{
			char *str = handle_env(last->content, *(shell->env_list));
			if(str)
			{
				free(last->content);
				last->content = str;
			}
		}
		write(fd[1], last->content, ft_strlen(last->content));
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}
