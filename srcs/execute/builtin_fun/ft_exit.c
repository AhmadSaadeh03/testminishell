/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:12:15 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/28 17:35:19 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_invalid_arg(int check_f, t_minishell *shell)
{
	printf("exit\n");
	if (check_f == 2)
	{
		free_exit(shell);
		exit(255);
	}
	else if (check_f == 1)
	{
		free_exit(shell);
		print_error("numeric argument required\n", "exit: ");
		exit(2);
	}
}

void	ft_exit(t_minishell *shell, char **cmd_line)
{
	int	exit_status;
	int	check_f;
	int temp = shell->last_exit;
	if (cmd_line[1] == NULL)
	{
		printf("exit\n");
		free_exit(shell);
		exit(temp);
	}
	if (cmd_line[2] != NULL)
	{
		print_error("too many arguments\n", "exit: ");
		shell->last_exit = 1;
		return ;
	}
	check_f = check_digit(cmd_line[1]);
	if (check_f != 3)
		handle_invalid_arg(check_f, shell);
	exit_status = ft_atoi(cmd_line[1]);
	shell->last_exit = exit_status;
	free_exit(shell);
	printf("exit\n");
	exit(exit_status);
}

int	is_valid_number_format(char *arg, int *sign, long *number)
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
		if (ft_isdigit(arg[i]) == 0)
			return (1);
		dig = arg[i] - '0';
		if (*number > (LONG_MAX - dig) / 10)
			return (2);
		*number = (*number * 10) + dig;
		i++;
	}
	return (0);
}

int	check_digit(char *arg)
{
	int		sign;
	long	number;
	int		result;
	long	full_num;

	sign = 1;
	number = 0;
	result = is_valid_number_format(arg, &sign, &number);
	if (result != 0)
		return (result);
	full_num = number * sign;
	if (full_num < INT_MIN || full_num > INT_MAX)
		return (2);
	return (3);
}
