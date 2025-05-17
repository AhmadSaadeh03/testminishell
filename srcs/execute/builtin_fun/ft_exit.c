/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:12:15 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/16 15:50:32 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_exit(t_minishell *shell, char **cmd_line)
{
	int	i;
	int	exit_status;

	i = 1;
	if (cmd_line[i] == NULL)
	{
		printf("exit\n");
		free_exit(shell);
		exit(EXIT_SUCCESS);
	}
	if (cmd_line[i + 1] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}
	if (check_digit(cmd_line[i]) != 3)
	{
		if (check_digit(cmd_line[i]) == 2)
		{
			free_exit(shell);
			printf("exit\n");
			exit(2);
		}
		else
		{
			free_exit(shell);
			printf("exit\n");
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		exit_status = ft_atoi(cmd_line[i]);
		shell->last_exit = exit_status;
		free_exit(shell);
		printf("exit\n");
		exit(exit_status);
	}
}

int	is_valid_number_format(const char *arg, int *sign, long *number)
{
	int	i;
	int	dig;

	i = 0;
	*number = 0;
	*sign = 1;
	if (arg == NULL || arg[0] == '\0')
		return (1);
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			*sign = -1;
		i++;
	}
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9' || ft_isdigit(arg[i]) == 0)
			return (1);
		dig = arg[i] - '0';
		if (*number > (LONG_MAX - dig) / 10)
			return (2);
		*number = (*number * 10) + dig;
		i++;
	}
	return (0);
}

int	check_digit(const char *arg)
{
	int		sign;
	long	number;
	int		result;

	result = is_valid_number_format(arg, &sign, &number);
	if (result != 0)
		return (result);
	number *= sign;
	if (number < INT_MIN || number > INT_MAX)
		return (2);
	return (3);
}
