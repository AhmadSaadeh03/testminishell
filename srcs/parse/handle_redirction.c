/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:30:14 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/19 18:40:34 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_redirection(t_cmd *cmd, t_minishell *shell)
{
	t_redirect	*redir;

	if (cmd->heredoc_flag == 1)
		exec_heredoc(cmd, shell);
	redir = cmd->redirect;
	while (redir)
	{

		if (redir->type == TOKEN_REDIRECT_IN)
		{
			if (redirect_in(redir->file_name) == 1)
				return (1);
		}
		else if (redir->type == TOKEN_REDIRECT_OUT
				|| redir->type == TOKEN_APPEND)
		{
			if (redirect_out(redir->file_name, redir->type) == 1)
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}
// >
int	redirect_out(char *file_name, t_type type)
{
	int	fd_out;
	if (type == TOKEN_REDIRECT_OUT || type == TOKEN_APPEND)
	{
		if (type == TOKEN_APPEND)
			fd_out = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd_out = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			perror("redirect_out");
			return (1);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	return (0);
}

int	redirect_in(char *file_name)
{
	int	fd_in;
	fd_in = open(file_name, O_RDONLY);
	if (fd_in == -1)
	{
		perror(file_name);
		return (1);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (0);
}

void	exec_heredoc(t_cmd *cmd, t_minishell *shell)
{
	t_here	*herd;
	(void)shell;
	herd = cmd->heredocs;
	while (herd)
	{
		herd->content = read_input(herd->limt);
		herd = herd->next;
	}
}

char	*read_input(char *limiter)
{
	char	*line;
	char	*cont;
	char	*tmp;

	cont = add_cmd("");
	if (!cont)
		return (NULL);
	//printf("sad");

	handle_signals(4);
	while (1)
	{
		line = readline("> ");
		//handle_signals(4);
		if (!line)
		{
			//printf("read_line error\n");
			break ;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		tmp = ft_strjoin(cont, line);
		if (!tmp)
		{
			free(line);
			free(cont);
			return (NULL);
		}
		free(cont);
		cont = tmp;
		tmp = ft_strjoin(cont, "\n");
		free(cont);
		if (!tmp)
		{
			free(line);
			return (NULL);
		}
		cont = tmp;
		free(line);
	}
	return (cont);
}
