/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:35:31 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/06 12:32:05 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtin(t_minishell *shell, char **cmd_line)
{
	if (!shell || !(*shell->cmd_list))
		return ;
	if (ft_strcmp(cmd_line[0], "echo") == 0)
		ft_echo(shell, cmd_line);
	else if (ft_strcmp(cmd_line[0], "cd") == 0)
		ft_cd(shell, cmd_line);
	else if (ft_strcmp(cmd_line[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd_line[0], "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(cmd_line[0], "export") == 0)
		ft_export(shell, cmd_line);
	else if (ft_strcmp(cmd_line[0], "unset") == 0)
		ft_unset(shell, cmd_line);
	else if (ft_strcmp(cmd_line[0], "exit") == 0)
		ft_exit(shell, cmd_line);
	else
		return ;
}

void	ft_cd(t_minishell *shell, char **cmd_line)
{
	char	*path;

	path = my_getenv((*shell->env_list), "HOME");
	if (cmd_line[1] == NULL)
	{
		if (chdir(path) != 0)
			perror("cd");
	}
	else
	{
		if (chdir(cmd_line[1]) != 0)
			perror("cd");
	}
	free(path);
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
}

void	ft_env(t_minishell *shell)
{
	print_env_list(shell->env_list);
}

void	ft_unset(t_minishell *shell, char **cmd_line)
{
	if (cmd_line[1])
		my_unsetenv(shell->env_list, cmd_line[1]);
	else
		return ;
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
