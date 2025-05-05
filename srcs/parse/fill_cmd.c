/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:31:06 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/05 17:26:19 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	store_last_arg(t_minishell *shell)
{
    t_cmd	*cmd;
    int		i;

    cmd = *(shell->cmd_list);
    i = 0;
	if (!cmd->cmd_line[i])
	{
		shell->last_arg = NULL;
		return ;
	}
	while (cmd->cmd_line[i])
	{
		if (cmd->cmd_line[i][0] == '$' && cmd->cmd_line[i][1] == '_')
			shell->print_last_arg = shell->last_arg;
		i++;
	}
	i = 0;
	while (cmd->cmd_line[i + 1])
		i++;
	shell->last_arg = add_cmd(cmd->cmd_line[i]);
	if (!shell->last_arg)
		return ;
}

void	add_redirect(t_cmd *cmd, char *file_name, t_type type)
{
	t_redirect	*new;
	t_redirect	*curr;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return ;
	new->file_name = NULL;
	new->file_name = add_cmd(file_name);
	if (new->file_name[0] == '"' || new->file_name[0] == 39)
		new->file_name = ft_trim_quotes(new->file_name);
	new->type = type;
	new->next = NULL;
	if (!cmd->redirect)
		cmd->redirect = new;
	else
	{
		curr = cmd->redirect;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}


int	fill_cmd(t_cmd *cmd2, t_node *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		if (temp->next && (temp->cmd_type == TOKEN_APPEND
				|| temp->cmd_type == TOKEN_REDIRECT_IN
				|| temp->cmd_type == TOKEN_REDIRECT_OUT))
		{
			add_redirect(cmd2, temp->next->node, temp->cmd_type);
			cmd2->redir_flag = 1;
			temp = temp->next;
		}
		else if (temp->cmd_type == TOKEN_HEREDOC && temp->next)
		{
			add_heredoc(cmd2, temp->next->node);
			cmd2->heredoc_flag = 1;
			temp = temp->next;
		}
		else if (temp->cmd_type == TOKEN_PIPE && temp->next)
		{
			cmd2->cmd_line[i] = NULL;
			cmd2->next = init_cmd();
			if (!cmd2->next)
				return (1);
			cmd2 = cmd2->next;
			i = 0;
		}
		else if (temp->node && (temp->cmd_type == TOKEN_ARG || temp->cmd_type == COMMAND))
		{
			cmd2->cmd_line[i] = add_cmd(temp->node);
			if (!cmd2->cmd_line[i])
				return (1);
			i++;
		}
		temp = temp->next;
	}
	cmd2->cmd_line[i] = NULL;
	return (0);
}

int	cmd_filling(t_minishell *shell)
{
	t_cmd	*cmd;
	t_node	*temp;

	cmd = init_cmd();
	if (!cmd)
		return (1);
	temp = shell->token_list;
	if (fill_cmd(cmd, temp) == 1)
		return (1);
	shell->cmd_list = malloc(sizeof(t_cmd *));
	if (!shell->cmd_list)
		return (1);
	*(shell->cmd_list) = cmd;
	store_last_arg(shell);
	free_tokens(shell->token_list);
	return (0);
}

char	*add_cmd(char *token)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = NULL;
	cmd = malloc(sizeof(char) * ft_strlen(token) + 1);
	if (!cmd)
		return (NULL);
	while (token[i])
	{
		cmd[i] = token[i];
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}

t_here	*creat_heredoc(char	*limit)
{
	t_here	*redir;

	redir = malloc(sizeof(t_here));
	if (!redir)
		return (NULL);
	redir->content = NULL;
	redir->limt = NULL;
	redir->limt = add_cmd(limit);
	redir->next = NULL;
	return (redir);
}

void	add_heredoc(t_cmd *cmd, char *limit)
{
	t_here	*new;
	t_here	*cur;

	new = creat_heredoc(limit);
	if (!new)
		return ;
	if (!cmd->heredocs)
		cmd->heredocs = new;
	else
	{
		cur = cmd->heredocs;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}
