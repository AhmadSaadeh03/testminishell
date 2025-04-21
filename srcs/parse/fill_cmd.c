/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:31:06 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/19 15:46:10 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_cmd(t_cmd *cmd, char *file_name, char *var, t_type type)
{
	if (type == TOKEN_REDIRECT_IN || type == TOKEN_HEREDOC)
	{
		if (type == TOKEN_HEREDOC && ft_strcmp(var, "<<") == 0)
		{
			cmd->limiter = ft_strdup(file_name);
			cmd->redirect = ft_strdup(var);
		}
		else
		{
			cmd->redirect = ft_strdup(var);
			cmd->file_in = ft_strdup(file_name);
		}
	}
	else if (type == TOKEN_REDIRECT_OUT || type == TOKEN_APPEND)
	{
		if (type == TOKEN_APPEND)
			cmd->append = 1;
		cmd->redirect = ft_strdup(var);
		cmd->file_out = ft_strdup(file_name);
	}
}

int	fill_cmd(t_cmd *cmd2, t_node *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		if (temp->next && (temp->cmd_type == TOKEN_HEREDOC
				|| temp->cmd_type == TOKEN_APPEND
				|| temp->cmd_type == TOKEN_REDIRECT_IN
				|| temp->cmd_type == TOKEN_REDIRECT_OUT))
		{
			set_cmd(cmd2, temp->next->node, temp->node, temp->cmd_type);
			temp = temp->next;
		}
		else if (temp->cmd_type == TOKEN_PIPE && temp->next)
		{
			if (cmd2)
			{
				init_cmd(&cmd2->next);
				cmd2 = cmd2->next;
				cmd2->pipe = ft_strdup("|");
				if (!cmd2->pipe)
					return (1);
				i = 0;
			}
		}
		else if (temp->node && (temp->cmd_type == TOKEN_ARG
					|| temp->cmd_type == COMMAND))
		{
			cmd2->cmd_line[i] = ft_strdup(temp->node);
			if (!cmd2->cmd_line[i])
				return (1);
			cmd2->cmd_line[++i] = NULL;
		}
		temp = temp->next;
	}
	return (0);
}

int	cmd_filling(t_minishell *shell)
{
	t_cmd	*cmd;
	t_node	*temp;

	init_cmd(&cmd);
	if (!cmd)
		return (1);
	temp = shell->token_list;
	if(fill_cmd(cmd, temp) == 1)
		return (1);
	shell->cmd_list = &cmd;
	free_tokens(shell->token_list);
	handle_redirection(&shell);
	return (0);
}
