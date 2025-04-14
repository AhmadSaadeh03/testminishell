/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:42:51 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/14 15:15:34 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *ft_trim_quotes(char *str)
{
	int i, j;
	char *new_str;
	int in_double_quotes = 0;
	int in_single_quotes = 0;

	if (!str)
		return (NULL);

	new_str = malloc(ft_strlen(str) + 1); // Allocate memory for the new string
	if (!new_str)
		return (NULL);

	i = 0;
	j = 0;

	// Check for leading single or double quotes
	if (str[i] == '"' || str[i] == '\'')
	{
		char quote_type = str[i]; // Store the type of the outer quote (single or double)
		new_str[j++] = str[i];  // Preserve the opening quote
		i++; // Skip the first quote

		while (str[i]) // Process the rest of the string
		{
			if (str[i] == quote_type) // If we encounter the closing quote, stop
				break;
			new_str[j++] = str[i]; // Copy the character as is
			i++;
		}
		new_str[j++] = str[i]; // Preserve the closing quote
		i++; // Skip the closing quote
	}
	// Process the string character by character for any quotes inside
	while (str[i])
	{
		if (str[i] == '"') // Handle double quotes inside
		{
			if (!in_single_quotes) // Toggle only if not inside single quotes
				in_double_quotes = !in_double_quotes;
			new_str[j++] = str[i]; // Preserve the double quote
		}
		else if (str[i] == '\'') // Handle single quotes inside
		{
			if (!in_double_quotes) // Toggle only if not inside double quotes
				in_single_quotes = !in_single_quotes;
			new_str[j++] = str[i]; // Preserve the single quote
		}
		else // Copy all other characters
		{
			new_str[j++] = str[i];
		}
		i++;
	}
	new_str[j] = '\0';

	return (new_str);
}

void	restore_spaces(char **tokens)
{
	int	i;
	int	j;

	i = 0;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			if (tokens[i][j] == '\a')
				tokens[i][j] = ' ';
			j++;
		}
		i++;
	}
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

char	*space_before_op(char *str, int i, int *len)
{
	int		new_len;
	char	*new_str;

	new_len = *len + 1;
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str, i);
	new_str[i] = ' ';
	ft_memcpy(new_str + i + 1, str + i, *len - i + 1);
	free(str);
	*len = new_len;
	return (new_str);
}

char	*space_after_op(char *str, int i, int *len)
{
	int		new_len;
	char	*new_str;

	new_len = *len + 1;
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str, i + 1);
	new_str[i + 1] = ' ';
	ft_memcpy(new_str + i + 2, str + i + 1, *len - i);
	free(str);
	*len = new_len;
	return (new_str);
}
