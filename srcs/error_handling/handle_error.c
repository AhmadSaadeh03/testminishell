/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:16:34 by asaadeh           #+#    #+#             */
/*   Updated: 2025/04/13 12:50:05 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_operation(t_minishell *shell)
{
	int	len;

	len = ft_strlen(shell->name);
	if (has_operator_at_edges(shell->name, len))
		return (1);
	if (has_invalid_repeated_operators(shell->name))
		return (1);
	return (0);
}

int	has_operator_at_edges(char *str, int len)
{
	if ((str[0] == '|') || (str[len - 1] == '|' || str[len - 1] == '>'
			|| str[len - 1] == '<'))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	has_invalid_repeated_operators(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
		{
			printf("syntax error near unexpected token '|'\n");
			return (1);
		}
		if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
		{
			printf("syntax error near unexpected token 'append or herdoc'\n");
			return (1);
		}
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
		{
			printf("syntax error near unexpected token 'append or herdoc'\n");
			return (1);
		}
		i++;
	}
	return (0);
}
