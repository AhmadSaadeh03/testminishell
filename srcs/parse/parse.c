/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:24:49 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/27 17:24:36 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parsing(t_minishell **shell)
{
	if (put_type(shell) == 1)
		return (1);
	return (0);
}

int	put_type(t_minishell **shell)
{
	t_node	*temp;

	temp = (*shell)->token_list;
	temp = fix_redirection(temp);
	if (!temp)
		return (1);
	while (temp)
	{
		if (temp->next && (ft_strcmp(temp->node, "<") == 0))
		{
			temp->cmd_type = TOKEN_REDIRECT_IN;
			temp->next->cmd_type = FILEIN;
			temp = temp->next;
		}
		else if (temp->next && (ft_strcmp(temp->node, ">") == 0))
		{
			temp->cmd_type = TOKEN_REDIRECT_OUT;
			temp->next->cmd_type = FILEOUT;
			temp = temp->next;
		}
		else if (temp->next && (ft_strcmp(temp->node, ">>") == 0))
		{
			temp->cmd_type = TOKEN_APPEND;
			temp->next->cmd_type = FILEOUT;
			temp = temp->next;
		}
		else if (temp->next && (ft_strcmp(temp->node, "<<") == 0))
		{
			temp->cmd_type = TOKEN_HEREDOC;
			temp->next->cmd_type = FILEIN;
			temp = temp->next;
		}
		else if (ft_strcmp(temp->node, "|") == 0 && temp->next)
			temp->cmd_type = TOKEN_PIPE;
		else
			temp->cmd_type = TOKEN_ARG;
		temp = temp->next;
	}
	return (0);
}

static int	fix_heredoc_merge(t_node **temp)
{
	t_node	*to_free;

	if ((*temp)->next && (*temp)->next->next
		&& ft_strcmp((*temp)->node, "<") == 0
		&& ft_strcmp((*temp)->next->node, "<") == 0)
	{
		to_free = (*temp)->next;
		(*temp)->next = (*temp)->next->next;
		free_node(to_free);
		free((*temp)->node);
		(*temp)->node = ft_strdup("<<");
		if (!(*temp)->node)
			return (0);
		*temp = (*temp)->next;
	}
	return (1);
}

static int	fix_append_merge(t_node **temp)
{
	t_node	*to_free;

	if ((*temp)->next && (*temp)->next->next
		&& ft_strcmp((*temp)->node, ">") == 0
		&& ft_strcmp((*temp)->next->node, ">") == 0)
	{
		to_free = (*temp)->next;
		(*temp)->next = (*temp)->next->next;
		free_node(to_free);
		free((*temp)->node);
		(*temp)->node = ft_strdup(">>");
		if (!(*temp)->node)
			return (0);
		*temp = (*temp)->next;
	}
	return (1);
}

t_node	*fix_redirection(t_node *list)
{
	t_node	*temp;

	temp = list;
	while (temp)
	{
		if (!fix_heredoc_merge(&temp))
			return (NULL);
		if (!fix_append_merge(&temp))
			return (NULL);
		temp = temp->next;
	}
	return (list);
}
