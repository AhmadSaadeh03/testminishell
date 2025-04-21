/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:36:47 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/19 16:37:45 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
