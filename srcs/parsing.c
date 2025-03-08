/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:42:55 by fghanem           #+#    #+#             */
/*   Updated: 2025/02/27 16:03:19 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishill.h"

void	init_cmd(t_cmd *cmd)
{
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	cmd->append = 0;
	cmd->args = malloc(sizeof(char *) * 100);
	cmd->input_file = NULL;
	cmd->output_file = NULL;
}

t_cmd	*parsing_tokens(t_minishell *tokens_l)
{
	t_cmd	*cmd;
	t_node	*temp;
	t_cmd_list	*cmd_list;
	int		i;

	init_cmd(cmd);
	temp = tokens_l->token_list;
	i = 0;
	while (temp)
	{
		if (ft_strcmp(temp->node, "<") == 0)
			cmd->input_file = ft_strdup(temp->node);
		else if (ft_strcmp(temp->node, ">") == 0)
			cmd->output_file = ft_strdup(temp->node);
		else if (ft_strcmp(temp->node, ">>") == 0)
		{
			cmd->output_file = ft_strdup(temp->node);
			cmd->append = 1;
		}
		else
			cmd->args[i++] = ft_strdup(temp->node);
		temp = temp->next;
	}
	cmd->args[i] = NULL; 
	return (cmd);
}

t_cmd_list	*classify_cmd(t_minishell *shell)
{
	t_parser	*pars;
	t_cmd_list	**cmd_list;
	t_node		*temp;
	
	temp = shell->token_list;
	while(temp)
	{
		if(temp->node == "ls")
		{
			(*cmd_list)->type = TOKEN_WORD;
			(*cmd_list)->value = "ls";
			(*cmd_list) = (*cmd_list)->next;
		}
		
	}
}
