/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:42:51 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/31 12:55:01 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_initial_quote_block(char *str, char *new_str, int *i_ptr)
{
	int		i;
	int		j;
	char	quote_type;

	i = *i_ptr;
	j = 0;
	if (str[i] == '"' || str[i] == '\'')
	{
		quote_type = str[i];
		new_str[j++] = str[i];
		i++;
		while (str[i])
		{
			if (str[i] == quote_type)
				break ;
			new_str[j++] = str[i];
			i++;
		}
		new_str[j++] = str[i];
		i++;
	}
	*i_ptr = i;
	return (j);
}

static int	handle_rest_of_string(char *str, char *new_str, int i, int j)
{
	int	in_double_quotes;
	int	in_single_quotes;

	in_double_quotes = 0;
	in_single_quotes = 0;
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
	return (j);
}

char	*ft_trim_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = handle_initial_quote_block(str, new_str, &i);
	j = handle_rest_of_string(str, new_str, i, j);
	new_str[j] = '\0';
	return (new_str);
}
