/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:16:34 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/31 12:58:30 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_operation(t_minishell *shell)
{
	int	len;

	len = ft_strlen(shell->name);
	if (has_invalid_repeated_operators(shell->name))
	{
		shell->last_exit = 127;
		return (1);
	}
	if (has_operator_at_edges(shell->name, len))
	{
		shell->last_exit = 127;
		return (1);
	}
	return (0);
}

int	has_operator_at_edges(char *str, int len)
{
	if (str[0] == '|' || (str[len - 1]) == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if ((str[len - 1]) == '>' || (str[len - 1]) == '<')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

void	print_error(char *mess, char *type)
{
	char	buffer[512];

	if (!mess || !type)
		return ;
	ft_strlcpy(buffer, "minishell: ", sizeof(buffer));
	ft_strlcat(buffer, type, sizeof(buffer));
	ft_strlcat(buffer, mess, sizeof(buffer));
	write(2, buffer, ft_strlen(buffer));
}
