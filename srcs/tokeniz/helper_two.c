/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:59:27 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/31 12:54:33 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	handle_char_in_quotes(char c, int *inside_single,
	int *inside_double)
{
	if (c == '"' && !(*inside_double) && !(*inside_single))
		*inside_double = 1;
	else if (c == '"' && *inside_double)
		*inside_double = 0;
	else if (c == '\'' && !(*inside_single) && !(*inside_double))
		*inside_single = 1;
	else if (c == '\'' && *inside_single)
		*inside_single = 0;
	if (c == ' ' && (*inside_single || *inside_double))
		return ('\a');
	return (c);
}

char	*replace_spaces_inside_quotes(char *input)
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
		temp[j] = handle_char_in_quotes(input[i], &inside_single,
				&inside_double);
		j++;
		i++;
	}
	temp[j] = '\0';
	return (temp);
}
