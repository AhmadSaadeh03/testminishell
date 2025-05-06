/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoom <fatoom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:29:56 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/06 21:52:02 by fatoom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_node *list)
{
	t_node	*tmp;

	if (!list)
		return ;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->node);
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;

	while (cmd)
	{
		i = 0;
		temp = cmd;
		cmd = cmd->next;
		if (temp->cmd_line)
		{
			while (temp->cmd_line[i])
				free(temp->cmd_line[i++]);
			free(temp->cmd_line);
		}
		free_here_list(temp->heredocs);
		free_redir_list(temp->redirect);
		free(temp);
	}
}

void	free_here_list(t_here *heredocs)
{
	printf("hhhhhhhhhhhhhhh\n");
	t_here	*tmp;

	if (!heredocs)
		return ;
	while (heredocs)
	{
		tmp = heredocs->next;
		if (heredocs->limt)
			free(heredocs->limt);
		if (heredocs->content)
			free(heredocs->content);
		free(heredocs);
		heredocs = tmp;
	}
}

void	free_redir_list(t_redirect *redir)
{
	t_redirect	*temp;

	if (!redir)
		return ;
	while (redir)
	{
		temp = redir->next;
		if (redir->file_name)
			free(redir->file_name);
		free(redir);
		redir = temp;
	}
}

void	free_exit(t_minishell *shell)
{
	free_array(shell->envps);
	if (*(shell->cmd_list))
		free_cmd(*(shell->cmd_list));
	free(shell->cmd_list);
	free_env_list(*(shell->env_list));
	free(shell->env_list);
	if (shell->token_space)
		free_array(shell->token_space);
	free(shell);
	shell = NULL;
}
