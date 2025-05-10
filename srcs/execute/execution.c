/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:49:35 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/10 13:42:51 by fghanem          ###   ########.fr       */
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
	{
		perror("fork");
		free_exit(shell);
		return ;
	}
	if (pid == 0)
	{
		if (handle_redirection(cmd, shell) == 1)
		{
			free_here_list(cmd->heredocs);
			free_exit(shell);
			exit(1);
		}
		if (fl == 1)
			exec_builtin(shell, cmd->cmd_line);
		else
			get_path_cmd(shell, cmd->cmd_line);
		free_exit(shell);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
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
		free_exit(shell);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}
