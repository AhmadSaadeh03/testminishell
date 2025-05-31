/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:38:31 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/30 20:54:56 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_quote_toggle(char c, char *quote)
{
	if ((c == '\'' || c == '"') && (!*quote || *quote == c))
	{
		if (*quote == 0)
			*quote = c;
		else
			*quote = 0;
		return (1);
	}
	return (0);
}

int	is_invalid_operator_sequence(char *s)
{
	if (s[0] == '|' && s[1] == '|')
	{
		printf("minishell: syntax error near unexpected token '||'\n");
		return (1);
	}
	if (s[0] == '>' && s[1] == '>' && s[2] == '>')
	{
		printf("syntax error near unexpected token '>'\n");
		return (1);
	}
	if (s[0] == '<' && s[1] == '<' && s[2] == '<')
	{
		printf("syntax error near unexpected token '<'\n");
		return (1);
	}
	return (0);
}

int	has_invalid_repeated_operators(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (is_quote_toggle(str[i], &quote))
		{
			i++;
			continue ;
		}
		if (!quote && is_invalid_operator_sequence(&str[i]))
			return (1);
		i++;
	}
	return (0);
}
