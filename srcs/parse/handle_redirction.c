/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:30:14 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/19 16:58:58 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redirection(t_minishell **shell)
{
	t_cmd	*cmd;

	cmd = (*(*shell)->cmd_list);
	while (cmd)
	{
		if (cmd->file_in)
			redirect_in(cmd);
		if (cmd->file_out)
			redirect_out(cmd);
		cmd = cmd->next;
	}
}
// >
void	redirect_out(t_cmd *cmd)
{
	int	fd_out;

	if (cmd->append)
		fd_out = open(cmd->file_out, O_RDONLY | O_CREAT | O_APPEND,
				0644);
	else
		fd_out = open(cmd->file_out, O_RDONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		perror(cmd->file_out);
	// dup2(fd_out, STDIN_FILENO);
	close(fd_out);
}
// <
void	redirect_in(t_cmd *cmd)
{
	int	fd_in;

	if (ft_strcmp(cmd->redirect, "<<") == 0)
		here_doc(cmd);
	fd_in = open(cmd->file_in, O_RDONLY);
	if (fd_in < 0)
		perror(cmd->file_in);
	close(fd_in);
}

// << not working yet

void	here_doc(t_cmd *cmd)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, cmd->limiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	close(pipefd[0]);
}
