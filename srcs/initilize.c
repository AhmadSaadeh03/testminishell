/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:28:26 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/05 16:10:48 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	*init_shell(char **envp)
{
	t_minishell	*shell;

	shell = NULL;
	shell = malloc(sizeof(t_minishell));
	if (!shell)
	{
		perror("Memory allocation failed for shell.\n");
		return (NULL);
	}
	shell->token_list = NULL;
	shell->token_space = NULL;
	shell->name = NULL;
	shell->cmd_list = NULL;
	shell->env_list = NULL;
	shell->envps = NULL;
	shell->last_arg = NULL;
	shell->print_last_arg = NULL;
	shell->env_list = malloc(sizeof(t_env));
	if (!shell->env_list)
	{
		free(shell);
		return (NULL);
	}
	(*shell->env_list) = copy_env_to_list(envp);
	shell->last_exit = 0;
	return (shell);
}

t_cmd	*init_cmd()
{
	t_cmd	*cmd;

	cmd = NULL;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("Memory allocation failed");
		return (NULL);
	}
	cmd->cmd_line = malloc(50 * sizeof(char *));
	if (!cmd->cmd_line)
	{
		free(cmd);
		perror("Memory allocation failed");
		return (NULL);
	}
	cmd->redirect = NULL;
	cmd->heredoc_flag = 0;
	cmd->redir_flag = 0;
	cmd->pipes.cmd_count = 0;
	cmd->pipes.pipe_fd = 0;
	cmd->heredocs = NULL;
	// cmd->pipes = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_node	*create_node_list(char **tokens)
{
	int		i;
	t_node	*head;
	t_node	*current;
		t_node *new_node;

	i = 0;
	current = NULL;
	head = NULL;
	while (tokens[i])
	{
		if (tokens[i] == NULL)
		{
			printf("Error: NULL token encountered at index %d\n", i);
			return (NULL);
		}
		new_node = create_new_node(tokens[i]);
		if (!new_node)
			return (NULL);
		append_node(&head, &current, new_node);
		i++;
	}
	return (head);
}

void	append_node(t_node **head, t_node **current, t_node *new_node)
{
	if (!*head)
	{
		*head = new_node;
		*current = new_node;
	}
	else
	{
		(*current)->next = new_node;
		*current = new_node;
	}
}

t_node	*create_new_node(char *token)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
	{
		printf("Memory allocation failed\n");
		return (NULL);
	}
	new_node->node = ft_strdup(token);
	if (!new_node->node)
	{
		free(new_node);
		printf("Memory allocation for node failed\n");
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}
