/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:28:26 by asaadeh           #+#    #+#             */
/*   Updated: 2025/04/13 12:50:19 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	*init_shell(t_minishell *shell)
{
	shell = malloc(sizeof(t_minishell));
	if (!shell)
	{
		perror("Memory allocation failed for shell.\n");
		return (NULL);
	}
	shell->token_list = NULL;
	shell->token_space = NULL;
	shell->name = NULL;
	return (shell);
}

void	init_cmd(t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	if (!*cmd)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	(*cmd)->cmd_line = malloc(100 * sizeof(char *));
	if (!(*cmd)->cmd_line)
	{
		free(*cmd);
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	(*cmd)->cmd_line[0] = NULL;
	(*cmd)->file_in = NULL;
	(*cmd)->file_out = NULL;
	(*cmd)->append = 0;
	(*cmd)->next = NULL;
	(*cmd)->pipe = NULL;
	(*cmd)->limiter = NULL;
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
