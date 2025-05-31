/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:32:34 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/31 12:55:44 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	split(t_minishell *shell)
{
	if (!*shell->name || !shell->name)
		return (1);
	if (handle_quotes_and_operators(shell) == 1)
		return (1);
	if (split_space(shell) == 1)
		return (1);
	if (parsing(&shell) == 1)
		return (1);
	if (expand(shell) == 1)
		return (1);
	return (0);
}

static int	handle_operator_if_needed(t_minishell *shell, int i)
{
	if (shell->name[i] == '|' || shell->name[i] == '<' || shell->name[i] == '>')
	{
		if (handle_operation(shell) == 1)
			return (1);
		if (split_operation(shell, shell->name[i]) == 1)
			return (1);
	}
	return (0);
}

void	update_quote_state(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
	else if (c == '"' && !(*in_single))
		*in_double = !(*in_double);
}

int	handle_quotes_and_operators(t_minishell *shell)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (shell->name[i])
	{
		update_quote_state(shell->name[i], &in_single, &in_double);
		if (!in_single && !in_double)
		{
			if (handle_operator_if_needed(shell, i))
				return (1);
		}
		i++;
	}
	if (in_single || in_double)
	{
		ft_putstr_fd("Error: Unclosed quotes\n", 2);
		shell->last_exit = 2;
		return (1);
	}
	return (0);
}

void	process_node_list(t_minishell *shell)
{
	t_node	*temp;

	shell->token_list = create_node_list(shell->token_space);
	if (shell->token_list && shell->token_list->next == NULL
		&& shell->token_list->node && (shell->token_list->node[0] == '|'
			|| shell->token_list->node[0] == '<'
			|| shell->token_list->node[0] == '>'))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		shell->last_exit = 127;
		free_tokens(shell->token_list);
		free_array(shell->token_space);
	}
	temp = shell->token_list;
	while (temp->next)
		temp = temp->next;
	if ((ft_strcmp(temp->node, ">") == 0 || ft_strcmp(temp->node, "<") == 0
			|| ft_strcmp(temp->node, "|") == 0) && temp->next == NULL)
	{
		ft_putstr_fd("syntax error near unexpected token\n", 2);
		shell->last_exit = 127;
		free_tokens(shell->token_list);
		free_array(shell->token_space);
	}
}
