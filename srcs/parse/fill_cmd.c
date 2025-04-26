/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:31:06 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/26 16:37:39 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	store_last_arg(t_minishell *shell)
{
    t_cmd	*cmd;
    int		i;
	int j = 0;

    cmd = *shell->cmd_list; 
    i = 0;
    int arr = 0;
	while (cmd->cmd_line[arr])
	{
		if (cmd->cmd_line[arr][0] == '$' && cmd->cmd_line[arr][1] == '_')
		{
			shell->print_last_arg = shell->last_arg; 
			return;
		}
		arr++;
	}
	
    	while (cmd->cmd_line[i + 1])
    		i++;   
    	shell->last_arg = malloc(sizeof(char) * ft_strlen(cmd->cmd_line[i]) + 1);
	while (cmd->cmd_line[i][j])
	{
		shell->last_arg[j] = cmd->cmd_line[i][j];
		j++;
	}
	shell->last_arg[j] = '\0';
	//printf("Last argument: %s\n", shell->last_arg);
}

void	set_cmd(t_cmd *cmd, char *file_name, char *var, t_type type)
{
	if (type == TOKEN_REDIRECT_IN || type == TOKEN_HEREDOC)
	{
		if (type == TOKEN_HEREDOC && ft_strcmp(var, "<<") == 0)
		{
			cmd->limiter = add_cmd(file_name, cmd->limiter);
			cmd->redirect = add_cmd(var, cmd->redirect);
		}
		else
		{
			cmd->redirect = add_cmd(var, cmd->redirect);
			cmd->file_in = add_cmd(file_name, cmd->redirect);
		}
	}
	else if (type == TOKEN_REDIRECT_OUT || type == TOKEN_APPEND)
	{
		if (type == TOKEN_APPEND)
			cmd->append = 1;
		cmd->redirect = add_cmd(var, cmd->redirect);
		cmd->file_out = add_cmd(file_name, cmd->file_out);
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
				cmd2 = cmd2->next;
				cmd2= init_cmd();
				if (!cmd2)
					return (1);
				// cmd2->pipe = add_cmd("|", cmd2->pipe);
				// if (!cmd2->pipe)
				// 	return (1);
				i = 0;
			}
		}
		else if (temp->node && (temp->cmd_type == TOKEN_ARG
					|| temp->cmd_type == COMMAND))
		{
			cmd2->cmd_line[i] = add_cmd(temp->node, cmd2->cmd_line[i]);
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

	// printf("filling\n\n\n\n\n");
	cmd = init_cmd();
	if (!cmd)
		return (1);
	temp = shell->token_list;
	if (fill_cmd(cmd, temp) == 1)
		return (1);
	shell->cmd_list = &cmd;
	store_last_arg(shell);
	free_tokens(shell->token_list);
	// handle_redirection(&shell);
	return (0);
}

char	*add_cmd(char *token, char *cmd)
{
	int		i;

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
