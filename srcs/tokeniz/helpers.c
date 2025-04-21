/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:42:51 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/19 16:37:35 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_trim_quotes(char *str)
{
	int i, j;
	char *new_str;
	int in_double_quotes = 0;
	int in_single_quotes = 0;

	if (!str)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	if (str[i] == '"' || str[i] == '\'')
	{
		char quote_type = str[i];
		new_str[j++] = str[i];
		i++;
		while (str[i])
		{
			if (str[i] == quote_type)
				break;
			new_str[j++] = str[i];
			i++;
		}
		new_str[j++] = str[i];
		i++;
	}
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (!in_single_quotes)
				in_double_quotes = !in_double_quotes;
			new_str[j++] = str[i];
		}
		else if (str[i] == '\'')
		{
			if (!in_double_quotes)
				in_single_quotes = !in_single_quotes;
			new_str[j++] = str[i];
		}
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*replace_spaces_inside_quotes(const char *input)
{
	int		i;
	int		j;
	int		inside_double;
	int		inside_single;
	char	*temp;

	i = 0;
	j = 0;
	inside_double = 0;
	inside_single = 0;
	temp = malloc(ft_strlen(input) + 1);
	if (!temp)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '"' && !inside_double && !inside_single)
			inside_double = 1;
		else if (input[i] == '"' && inside_double)
			inside_double = 0;
		else if (input[i] == '\'' && !inside_single && !inside_double)
			inside_single = 1;
		else if (input[i] == '\'' && inside_single)
			inside_single = 0;
		if (input[i] == ' ' && (inside_single || inside_double))
			temp[j++] = '\a';
		else
			temp[j++] = input[i];
		i++;
	}
	temp[j] = '\0';
	return (temp);
}
