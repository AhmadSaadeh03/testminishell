/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:42:20 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/05 17:31:02 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    exec_pipe(t_minishell *shell)
{
    t_cmd   *curr;
    t_pipes pipe_data;
    int i;

    curr = *(shell->cmd_list);
    pipe_data = curr->pipes;
    i = 0;
    pipe_data.cmd_count = cmd_count(curr);
    if (open_pipes(&pipe_data) != 0)
        return ;
    pipe_data.pid = malloc(sizeof(pid_t) * pipe_data.cmd_count);
    if (!pipe_data.pid)
        return ;
    while (curr)
    {
        run_cmd(shell, curr, &pipe_data, i);
        curr = curr->next;
        i++;
    }
    close_fd(&pipe_data);
    i = 0;
    while (i < pipe_data.cmd_count)
        waitpid(pipe_data.pid[i++], NULL, 0);
    free(pipe_data.pipe_fd);
    free(pipe_data.pid);
}

int cmd_count(t_cmd *cmd)
{
    int count;

    count = 0;
    while (cmd)
    {
        count++;
        cmd = cmd->next;
    }
    return (count);
}

int open_pipes(t_pipes *pipe_data)
{
    int pipe_count;
    int i;

    i = 0;
    pipe_count = pipe_data->cmd_count - 1;
    pipe_data->pipe_fd = malloc(sizeof(int) * 2 * (pipe_count));
    if (!pipe_data->pipe_fd)
        return (1);
    while (i < pipe_count)
    {
        if (pipe(&pipe_data->pipe_fd[i * 2]) == -1)
        {
            perror("pipe");
            free(pipe_data->pipe_fd);
            return (1);
        }
        i++;
    }
    return (0);
}

void    run_cmd(t_minishell *shell, t_cmd *cmd, t_pipes *pipe_data, int  i)
{
    pipe_data->pid[i] = fork();
    if (pipe_data->pid[i] == -1)
    {
        perror("fork");
        // free(pipe_data->pid);
        // free(pipe_data->pipe_fd);
        return ;
    }
    if (pipe_data->pid[i] == 0)
    {
        if (i > 0)
            dup2(pipe_data->pipe_fd[(i - 1) * 2], STDIN_FILENO);
        if (i < (pipe_data->cmd_count - 1))
            dup2(pipe_data->pipe_fd[i * 2 + 1], STDOUT_FILENO);
        close_fd(pipe_data);
        execute_one_cmd(shell, cmd);
        exit(0);
    }
}

void    close_fd(t_pipes *pipe_data)
{
    int i;

    i = 0;
    while (i < (pipe_data->cmd_count - 1) * 2)
    {
        close(pipe_data->pipe_fd[i]);
        i++;
    }
}
