/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:19:14 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/31 12:55:32 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_spacing_around_operator(char *temp, int *i, int *len)
{
	if (*i > 0 && temp[*i - 1] != ' ')
	{
		temp = space_before_op(temp, *i, len);
		if (!temp)
			return (NULL);
		(*i)++;
	}
	if (*i + 1 < *len && temp[*i + 1] != ' ')
	{
		temp = space_after_op(temp, *i, len);
		if (!temp)
			return (NULL);
	}
	return (temp);
}

static	char	*process_operator_spacing(char *temp, char operator, int *len)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (i < *len)
	{
		if (temp[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (temp[i] == '"' && !in_single)
			in_double = !in_double;
		if (temp[i] == operator && !in_single && !in_double)
		{
			temp = handle_spacing_around_operator(temp, &i, len);
			if (!temp)
				return (NULL);
		}
		i++;
	}
	return (temp);
}

int	split_operation(t_minishell *shell, char operator)
{
	int		len;
	char	*temp;

	temp = ft_strdup(shell->name);
	if (!temp)
		return (1);
	len = ft_strlen(temp);
	temp = process_operator_spacing(temp, operator, &len);
	if (!temp)
		return (1);
	free(shell->name);
	shell->name = add_cmd(temp);
	if (!shell->name)
	{
		free (temp);
		return (1);
	}
	free(temp);
	return (0);
}

int	split_space(t_minishell *shell)
{
	char	*temp;

	temp = NULL;
	temp = replace_spaces_inside_quotes(shell->name);
	if (!temp)
		return (1);
	shell->token_space = ft_split(temp, ' ');
	if (!shell->token_space)
	{
		ft_putstr_fd("Error: Failed to split the input\n", 2);
		shell->last_exit = 2;
		return (1);
	}
	free(temp);
	free(shell->name);
	restore_spaces(shell->token_space);
	process_node_list(shell);
	free_array(shell->token_space);
	shell->token_space = NULL;
	return (0);
}
