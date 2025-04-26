/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:29:56 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/26 13:45:31 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_and_exit(t_minishell *shell)
{
	free_minishell(shell);
	exit(1);
}

void	free_tokens(t_node *list)
{
	t_node	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->node);
		free(tmp);
	}
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*curr;
	// int		i;

	curr = *cmd;
	// i = 0;
	while (curr)
	{
		free_array(curr->cmd_line);
		// free_array(curr->cmd_line);
		free(curr->file_in);
		free(curr->file_out);
		free(curr->limiter);
		free(curr->redirect);
		// if (curr->next != NULL)
		curr = curr->next;
	}
	free(cmd);
}

