/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:30:05 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/12 15:10:33 by fghanem          ###   ########.fr       */
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
		if (shell->name[i] == operator&& !inside_quotes)
			inside_quotes = 1;
		else if (shell->name[i] == operator&& inside_quotes)
		{
			inside_quotes = 0;
		}
		else if (inside_quotes)
			c++;
		i++;
	}
	return (c);
}
