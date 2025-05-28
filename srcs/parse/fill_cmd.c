/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoom <fatoom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:31:06 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/28 21:41:46 by fatoom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_redirect	*create_redirect_node(char *file_name, t_type type)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->file_name = NULL;
	if (file_name[0] == '"' && file_name[ft_strlen(file_name) - 1] == '"')
	{
		new->file_name = ft_trim_quotes(file_name);
		printf("file name : %s\n", new->file_name);
	}
	else
		new->file_name = add_cmd(file_name);
	if (!new->file_name)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_redirect(t_cmd *cmd, char *file_name, t_type type)
{
	t_redirect	*new;
	t_redirect	*curr;

	new = create_redirect_node(file_name, type);
	if (!new)
		return ;
	curr = new;
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

int	cmd_filling(t_minishell *shell)
{
	t_node	*temp;

	shell->cmd_list = malloc(sizeof(t_cmd *));
	if (!shell->cmd_list)
		return (1);
	*(shell->cmd_list) = init_cmd();
	if (!*(shell->cmd_list))
	{
		free(shell->cmd_list);
		return (1);
	}
	temp = shell->token_list;
	if (fill_cmd(*(shell->cmd_list), temp) == 1)
		return (1);
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

t_here	*creat_heredoc(char *limit)
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
