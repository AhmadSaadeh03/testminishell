/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoom <fatoom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:54:13 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/28 21:40:59 by fatoom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_redirections(t_cmd **cmd, t_node **temp)
{
	if ((*temp)->next && ((*temp)->cmd_type == TOKEN_APPEND
			|| (*temp)->cmd_type == TOKEN_REDIRECT_IN
			|| (*temp)->cmd_type == TOKEN_REDIRECT_OUT))
	{
		add_redirect(*cmd, (*temp)->next->node, (*temp)->cmd_type);
		(*cmd)->redir_flag = 1;
		*temp = (*temp)->next;
		return (1);
	}
	return (0);
}

static int	handle_heredoc(t_cmd **cmd, t_node **temp)
{
	if ((*temp)->cmd_type == TOKEN_HEREDOC && (*temp)->next)
	{
		add_heredoc(*cmd, (*temp)->next->node);
		(*cmd)->heredoc_flag = 1;
		*temp = (*temp)->next;
		return (1);
	}
	return (0);
}

static int	handle_command_args(t_cmd *cmd, t_node *temp, int *i)
{
	if (temp->node && (temp->cmd_type == TOKEN_ARG
			|| temp->cmd_type == COMMAND))
	{
		cmd->cmd_line[*i] = add_cmd(temp->node);
		if (!cmd->cmd_line[*i])
			return (0);
		(*i)++;
	}
	return (1);
}

int	fill_cmd(t_cmd *cmd2, t_node *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		if (handle_redirections(&cmd2, &temp))
			continue ;
		else if (handle_heredoc(&cmd2, &temp))
			continue ;
		else if (temp->cmd_type == TOKEN_PIPE && temp->next)
		{
			cmd2->cmd_line[i] = NULL;
			cmd2->next = init_cmd();
			if (!cmd2->next)
				return (1);
			cmd2 = cmd2->next;
			i = 0;
		}
		else
			handle_command_args(cmd2, temp, &i);
		temp = temp->next;
	}
	cmd2->cmd_line[i] = NULL;
	return (0);
}

int	parsing(t_minishell **shell)
{
	if (put_type(shell) == 1)
		return (1);
	return (0);
}
