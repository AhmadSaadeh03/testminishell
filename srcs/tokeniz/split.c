/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:32:34 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/26 17:21:33 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

// int	handle_quotes_and_operators(t_minishell *shell)
// {
// 	int	i;

// 	i = 0;
// 	while (shell->name[i])
// 	{
// 		if (shell->name[i] == '\'' || shell->name[i] == '"')
// 		{
// 			if (closed_quotes(shell, shell->name[i]) == 1)
// 			{
// 				ft_putstr_fd("Error: Unclosed quotes\n", 2);
// 				shell->last_exit = 2;
// 				return (1);
// 			}
// 		}
// 		if (shell->name[i] && (shell->name[i] == '|' || shell->name[i] == '<'
// 				|| shell->name[i] == '>'))
// 		{
// 			if (handle_operation(shell) == 1)
// 				return (1);
// 			if (split_operation(shell, shell->name[i]) == 1)
// 				return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
// int	handle_quotes_and_operators(t_minishell *shell)
// {
// 	int	i;
// 	int	in_single;
// 	int	in_double;

// 	in_single = 0;
// 	in_double = 0;
// 	i = 0;
// 	while (shell->name[i])
// 	{
// 		if (shell->name[i] == '\'' && !in_double)
// 			in_single = !in_single;
// 		else if (shell->name[i] == '"' && !in_single)
// 			in_double = !in_double;
// 		if ((shell->name[i] == '|' || shell->name[i] == '<'
// 				|| shell->name[i] == '>') && !in_single && !in_double)
// 		{
// 			if (handle_operation(shell) == 1)
// 				return (1);
// 			if (split_operation(shell, shell->name[i]) == 1)
// 				return (1);
// 		}
// 		if ((shell->name[i] == '\'' || shell->name[i] == '"')
// 				&& closed_quotes(shell, shell->name[i]) == 1)
// 		{
// 			ft_putstr_fd("Error: Unclosed quotes\n", 2);
// 			shell->last_exit = 2;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

static int	handle_operator_if_needed(t_minishell *shell, int i,
	int in_single, int in_double)
{
	if ((shell->name[i] == '|' || shell->name[i] == '<'
			|| shell->name[i] == '>') && !in_single && !in_double)
	{
		if (handle_operation(shell) == 1)
			return (1);
		if (split_operation(shell, shell->name[i]) == 1)
			return (1);
	}
	return (0);
}

int	handle_quotes_and_operators(t_minishell *shell)
{
	int	i;
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	i = 0;
	while (shell->name[i])
	{
		if (shell->name[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (shell->name[i] == '"' && !in_single)
			in_double = !in_double;
		if (handle_operator_if_needed(shell, i, in_single, in_double))
			return (1);
		if ((shell->name[i] == '\'' || shell->name[i] == '"')
			&& closed_quotes(shell, shell->name[i]) == 1)
		{
			ft_putstr_fd("Error: Unclosed quotes\n", 2);
			shell->last_exit = 2;
			return (1);
		}
		i++;
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
