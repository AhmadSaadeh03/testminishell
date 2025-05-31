/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:01:12 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/31 12:28:43 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_line_input(char **cont, char *line)
{
	char	*tmp;
	char	*join;

	join = ft_strjoin(*cont, line);
	free(line);
	if (!join)
	{
		free(*cont);
		return (0);
	}
	tmp = ft_strjoin(join, "\n");
	if (!tmp)
	{
		free(*cont);
		return (0);
	}
	free(join);
	free(*cont);
	*cont = tmp;
	return (1);
}

static int	handle_sigint_in_heredoc(t_minishell *shell, int fd, char *line,
		char *cont)
{
	shell->last_exit = g_signal + 128;
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(line);
	free(cont);
	return (1);
}

char	*read_input(char *limiter, t_minishell *shell)
{
	char	*line;
	char	*cont;
	int		fd;

	cont = add_cmd("");
	if (!cont)
		return (NULL);
	fd = dup(STDIN_FILENO);
	handle_signals(4);
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT && handle_sigint_in_heredoc(shell, fd, line,
				cont))
			(free_exit(shell), exit(0));
		if (!line || ft_strcmp(line, limiter) == 0)
			break ;
		if (line[0] == '\0')
			free(line);
		else if (!process_line_input(&cont, line))
			return (NULL);
	}
	free(line);
	close(fd);
	return (cont);
}

char	*read_input_pipe(char *limiter, t_minishell *shell)
{
	char	*line;
	char	*cont;
	int		fd;

	cont = add_cmd("");
	if (!cont)
		return (NULL);
	fd = dup(STDIN_FILENO);
	handle_signals(4);
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT && handle_sigint_in_heredoc(shell, fd, line,
				cont))
			return (NULL);
		if (!line || ft_strcmp(line, limiter) == 0)
			break ;
		if (line[0] == '\0')
			free(line);
		else if (!process_line_input(&cont, line))
			return (NULL);
	}
	free(line);
	close(fd);
	return (cont);
}

void	add_heredoc(t_cmd *cmd, char *limit)
{
	t_here	*new;
	t_here	*cur;

	new = creat_heredoc(limit);
	if (!new)
		return ;
	if (!cmd->heredocs)
		cmd->heredocs = new;
	else
	{
		cur = cmd->heredocs;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}
