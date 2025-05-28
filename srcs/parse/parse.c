/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoom <fatoom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:24:49 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/28 22:22:47 by fatoom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	assign_cmd_type(t_node *temp)
{
	if (temp->next && ft_strcmp(temp->node, "<") == 0)
	{
		temp->cmd_type = TOKEN_REDIRECT_IN;
		temp->next->cmd_type = FILEIN;
	}
	else if (temp->next && ft_strcmp(temp->node, ">") == 0)
	{
		temp->cmd_type = TOKEN_REDIRECT_OUT;
		temp->next->cmd_type = FILEOUT;
	}
	else if (temp->next && ft_strcmp(temp->node, ">>") == 0)
	{
		temp->cmd_type = TOKEN_APPEND;
		temp->next->cmd_type = FILEOUT;
	}
	else if (temp->next && ft_strcmp(temp->node, "<<") == 0)
	{
		temp->cmd_type = TOKEN_HEREDOC;
		temp->next->cmd_type = FILEIN;
	}
	else if (ft_strcmp(temp->node, "|") == 0 && temp->next)
		temp->cmd_type = TOKEN_PIPE;
	else
		temp->cmd_type = TOKEN_ARG;
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
		assign_cmd_type(temp);
		if ((temp->cmd_type == TOKEN_REDIRECT_IN
				|| temp->cmd_type == TOKEN_REDIRECT_OUT
				|| temp->cmd_type == TOKEN_APPEND
				|| temp->cmd_type == TOKEN_HEREDOC) && temp->next)
			temp = temp->next;
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
