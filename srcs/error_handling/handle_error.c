/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:16:34 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/24 14:50:06 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_operation(t_minishell *shell)
{
	int	len;

	len = ft_strlen(shell->name);
	if (has_operator_at_edges(shell->name, len))
	{
		shell->last_exit = 127;
		return (1);
	}
	if (has_invalid_repeated_operators(shell->name))
	{
		shell->last_exit = 127;
		return (1);
	}
	return (0);
}

int	has_operator_at_edges(char *str, int len)
{
	if ((str[0] == '|') || (str[len - 1] == '|' || str[len - 1] == '>'
			|| str[len - 1] == '<'))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	has_invalid_repeated_operators(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
		{
			printf("syntax error near unexpected token '|'\n");
			return (1);
		}
		if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
		{
			printf("syntax error near unexpected token 'append or herdoc'\n");
			return (1);
		}
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
		{
			printf("syntax error near unexpected token 'append or herdoc'\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_error(char *mess, char *type)
{
	char	*tmp1;
	char	*tmp2;
	char	*final;

	tmp1 = ft_strjoin("minishell: ", type);
	if (!tmp1)
		return ;
	tmp2 = ft_strjoin(tmp1, mess);
	free(tmp1);
	if (!tmp2)
		return ;
	final = ft_strdup(tmp2);
	free(tmp2);
	if (!final)
		return ;
	ft_putstr_fd(final, 2);
	free(final);
}
