/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoom <fatoom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:30:05 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/28 22:30:40 by fatoom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	closed_quotes(t_minishell *shell, char qoute)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (shell->name[i])
	{
		if (shell->name[i] == qoute)
			c++;
		i++;
	}
	if (c % 2 == 0)
		return (0);
	return (1);
}

int	handle_quote(t_minishell *shell, char operator)
{
	int	i;
	int	c;
	int	inside_quotes;

	i = 0;
	c = 0;
	inside_quotes = 0;
	while (shell->name[i])
	{
		if (shell->name[i] == operator && !inside_quotes)
			inside_quotes = 1;
		else if (shell->name[i] == operator && inside_quotes)
		{
			inside_quotes = 0;
		}
		else if (inside_quotes)
			c++;
		i++;
	}
	return (c);
}

int	is_all_whitespace(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}
