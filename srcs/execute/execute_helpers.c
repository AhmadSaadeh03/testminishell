/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:47:30 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/26 17:12:30 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	heredoc_child(t_cmd *cmd, t_minishell *shell)
{
	t_here	*last;
	int		fd[2];
	char	*str;

	if (pipe(fd) == -1)
		return ;
	last = cmd->heredocs;
	while (last->next)
		last = last->next;
	if (last && last->content)
	{
		if (ft_strchr(last->content, '$'))
		{
			str = handle_env(last->content, *(shell->env_list));
			if (str)
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

int	prepare_env_and_check(t_minishell *shell, char *cmd_path, char *arg)
{
	shell->envps = copy_env_list_to_array((*shell->env_list));
	if (!shell->envps)
		return (0);
	if (!cmd_path)
	{
		free_array(shell->envps);
		print_error(": command not found\n", arg);
		shell->last_exit = 127;
		return (0);
	}
	return (1);
}

char	**get_path_array(t_minishell *shell, char *arg)
{
	char	*path_env;

	path_env = my_getenv((*shell->env_list), "PATH");
	if (!path_env)
	{
		print_error(": No such file or directory\n", arg);
		shell->last_exit = 127;
		return (NULL);
	}
	return (ft_split(path_env, ':'));
}
