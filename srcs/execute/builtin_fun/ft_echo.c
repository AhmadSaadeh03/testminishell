/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoom <fatoom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:12:34 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/28 22:13:33 by fatoom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_ignore(char *cmd)
{
	if ((ft_strcmp(cmd, "-e") == 0) || (ft_strcmp(cmd,
				"-E") == 0))
		return (1);
	else if (cmd[0] == '-' && (cmd[1] == 'n'
			|| cmd[1] == 'e' || cmd[1] == 'E'))
		return (2);
	return (0);
}

void	ft_echo(t_minishell *shell, char **cmd_line, int newline)
{
	int	i;

	i = 1;
	while (cmd_line[i] != NULL)
	{
		if (is_ignore(cmd_line[i]) == 1)
		{
			i++;
			continue ;
		}
		else if (is_ignore(cmd_line[i]) == 2)
		{
			if (handle_echo_flag(cmd_line[i]) == 1)
			{
				newline = 0;
				i++;
				continue ;
			}
		}
		print_echo_args(cmd_line[i], shell->last_exit, cmd_line[i + 1] != NULL);
		i++;
	}
	shell->last_exit = 0;
	if (newline)
		printf("\n");
}

void	print_echo_args(char *arg, int status, int space_flag)
{
	char	*p;
	int		i;

	i = 0;
	p = arg;
	while (p[i])
	{
		if (p[i] == '$' && p[i + 1] == '?')
		{
			ft_putnbr_fd(status, 1);
			i += 2;
		}
		else
		{
			ft_putchar_fd(p[i], 1);
			i++;
		}
	}
	if (space_flag)
		write(1, " ", 1);
}

int	handle_echo_flag(char *arg)
{
	int	j;

	j = 0;
	if ((ft_strcmp(arg, "-e") == 0) || (ft_strcmp(arg, "-E") == 0))
		return (0);
	if (arg[j] == '-' && arg[j + 1] == 'n')
	{
		j++;
		while (arg[j])
		{
			if (arg[j] != 'n' && arg[j] != 'e' && arg[j] != 'E')
				return (0);
			j++;
		}
	}
	return (1);
}

void	handle_exit_status(t_minishell *shell, int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			shell->last_exit = g_signal + 128;
		else if (WTERMSIG(status) == SIGQUIT)
			shell->last_exit = 131;
	}
	else if (WIFEXITED(status))
		shell->last_exit = WEXITSTATUS(status);
}
