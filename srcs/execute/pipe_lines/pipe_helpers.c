/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:52:03 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/13 13:54:01 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	alloc_pipe_resources(t_pipes *p, int count)
{
	p->cmd_count = count;
	p->pid = malloc(sizeof(pid_t) * count);
	if (!p->pid)
		return (1);
	p->pipe_fd = malloc(sizeof(int) * 2 * (count - 1));
	if (!p->pipe_fd)
	{
		free(p->pid);
		return (1);
	}
	return (0);
}

int	init_pipe_data(t_pipes *p, int count)
{
	int	i;

	if (alloc_pipe_resources(p, count))
		return (1);
	i = 0;
	while (i < count - 1)
	{
		if (pipe(&p->pipe_fd[i * 2]) == -1)
		{
			perror("pipe");
			while (i > 0)
			{
				i--;
				close(p->pipe_fd[i * 2]);
				close(p->pipe_fd[i * 2 + 1]);
			}
			free(p->pid);
			free(p->pipe_fd);
			return (1);
		}
		i++;
	}
	return (0);
}

void	close_fd(t_pipes *pipe_data)
{
	int	i = 0;
	
	while (i < (pipe_data->cmd_count - 1) * 2)
	{	
		close(pipe_data->pipe_fd[i]);
		i++;
	}
    free(pipe_data->pipe_fd);
	pipe_data->pipe_fd = NULL;
}

void	free_pipe_data(t_pipes *pipe_data)
{
	int	i;

    i = 0; 
	while (i < (pipe_data->cmd_count - 1) * 2)
    {
		close(pipe_data->pipe_fd[i]);
        i++;
    }
    free(pipe_data->pipe_fd);
	free(pipe_data->pid);
	pipe_data->pipe_fd = NULL;
	pipe_data->pid = NULL;
	pipe_data->cmd_count = 0;
}
