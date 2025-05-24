/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:12:34 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/24 17:21:43 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_arg(char *arg, int has_next)
{
	printf("%s", arg);
	if (has_next)
		printf(" ");
}

void	ft_echo(t_minishell *shell, char **cmd_line)
{
	int		i;
	int		newline;
	int		flag_arg;

	i = 1;
	newline = 1;
	while (cmd_line[i] != NULL)
	{
		if (cmd_line[i] && (cmd_line[i][0] == '-'))
		{
			flag_arg = handle_echo_flag(cmd_line[i]);
			if (flag_arg == 1)
			{
				if (ft_strchr(cmd_line[i], 'n'))
					newline = 0;
			}
		}
		else if (cmd_line[i][0] == '$' && cmd_line[i][1] == '?')
			print_exit_status(shell, cmd_line[i]);
		else
			print_arg(cmd_line[i], cmd_line[i + 1] != NULL);
		i++;
	}
	if (newline)
		printf("\n");
}

void	print_exit_status(t_minishell *shell, char *arg)
{
	char	*exit;

	exit = ft_itoa(shell->last_exit);
	if (!exit)
		return ;
	handle_exit_status(exit, arg);
	shell->last_exit = 0;
	free(exit);
}

int	handle_echo_flag(char *arg)
{
	int	j;

	j = 0;
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

void	handle_exit_status(char *exit, char *arg)
{
	char	*suffix;
	char	*joined;

	suffix = ft_strdup(arg + 2);
	joined = ft_strjoin(exit, suffix);
	printf("%s", joined);
	free(suffix);
	free(joined);
}
