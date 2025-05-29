/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:51:55 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/29 14:21:30 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_before_equal(char *str)
{
	int		i;
	int		j;
	char	*before;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	before = malloc((i + 1) * sizeof(char));
	if (!before)
		return (NULL);
	j = 0;
	while (j < i)
	{
		before[j] = str[j];
		j++;
	}
	before[i] = '\0';
	return (before);
}

static int	skip_to_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	return (i);
}

static char	*get_after_equal(char *str, int i, int in_double_quote)
{
	int		j;
	char	*after;

	j = 0;
	after = malloc(ft_strlen(str + i) + 1);
	if (!after)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"')
		{
			in_double_quote = !in_double_quote;
			i++;
			continue ;
		}
		if (in_double_quote || ft_isalnum(str[i]) || str[i] == ' '
			|| (!in_double_quote && !ft_isalnum(str[i])))
			after[j++] = str[i];
		else
			break ;
		i++;
	}
	after[j] = '\0';
	return (after);
}

void	handle_export(char *str, t_env **env_list)
{
	char	*before_equal;
	char	*after_equal;
	int		i;

	if (ft_strchr(str, '=') != NULL)
	{
		before_equal = get_before_equal(str);
		if (!before_equal)
			return ;
		i = skip_to_value(str);
		after_equal = get_after_equal(str, i, 0);
		if (!after_equal)
		{
			free(before_equal);
			return ;
		}
		my_setenv(env_list, before_equal, after_equal);
		free(before_equal);
		free(after_equal);
	}
	else
	{
		my_setenv(env_list, str, NULL);
	}
}
