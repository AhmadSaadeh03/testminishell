/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoom <fatoom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:35:31 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/30 12:59:20 by fatoom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtin(t_minishell *shell, char **cmd_line)
{
	if (!shell || !(*shell->cmd_list))
		return ;
	if (ft_strcmp(cmd_line[0], "echo") == 0)
		ft_echo(shell, cmd_line, 1);
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
		{
			perror("cd");
			shell->last_exit = 1;
		}
		free(path);
	}
	else
	{
		if (cmd_line[2] != NULL)
		{
			print_error(" too many arguments\n", "cd: ");
			shell->last_exit = 1;
		}
		else if (chdir(cmd_line[1]) != 0)
		{
			print_error("No such file or directory\n", "cd: ");
			shell->last_exit = 1;
		}
	}
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

void	ft_env(t_minishell *shell)
{
	print_env_list(shell->env_list);
	shell->last_exit = 0;
}

void	ft_unset(t_minishell *shell, char **cmd_line)
{
	int	i;

	i = 1;
	while (cmd_line[i])
	{
		my_unsetenv(shell->env_list, cmd_line[i]);
		i++;
	}
}
