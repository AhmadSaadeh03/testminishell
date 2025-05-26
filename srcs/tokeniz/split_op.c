/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:19:14 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/26 17:20:22 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*process_operator_spacing(char *temp, char operator, int *len)
{
	int	i;

	i = 0;
	while (i < *len)
	{
		if (temp[i] == operator)
		{
			if (i > 0 && temp[i - 1] != ' ')
			{
				temp = space_before_op(temp, i, len);
				if (!temp)
					return (NULL);
				i++;
			}
			if (i + 1 < *len && temp[i + 1] != ' ')
			{
				temp = space_after_op(temp, i, len);
				if (!temp)
					return (NULL);
			}
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
	free(temp);
	return (0);
}

// int	split_operation(t_minishell *shell, char operator)
// {
// 	int		i;
// 	int		len;
// 	char	*temp;

// 	i = 0;
// 	temp = ft_strdup(shell->name);
// 	if (!temp)
// 		return (1);
// 	len = ft_strlen(temp);
// 	while (i < len)
// 	{
// 		if (temp[i] == operator)
// 		{
// 			if (i > 0 && temp[i - 1] != ' ')
// 			{
// 				temp = space_before_op(temp, i, &len);
// 				if (!temp)
// 					return (1);
// 				i++;
// 			}
// 			if (i + 1 < len && temp[i + 1] != ' ')
// 			{
// 				temp = space_after_op(temp, i, &len);
// 				if (!temp)
// 					return (1);
// 			}
// 		}
// 		i++;
// 	}
// 	free(shell->name);
// 	shell->name = add_cmd(temp);
// 	free(temp);
// 	return (0);
// }