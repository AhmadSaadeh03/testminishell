/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:29:56 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/19 16:30:17 by fghanem          ###   ########.fr       */
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

void free_cmd_list(t_cmd **cmd_list)
{
	t_cmd *current;
	t_cmd *tmp;
	int i;

	if (!cmd_list || !*cmd_list)
		return;
	current = *cmd_list;
	while (current)
	{
		tmp = current;
		current = current->next;
		if (tmp->cmd_line)
		{
			i = 0;
			while (tmp->cmd_line[i])
				free(tmp->cmd_line[i++]);
			free(tmp->cmd_line);
		}
		free(tmp->file_in);
		free(tmp->file_out);
		free(tmp->redirect);
		free(tmp->pipe);
		free(tmp->limiter);
		free(tmp);
	}
	*cmd_list = NULL;
}