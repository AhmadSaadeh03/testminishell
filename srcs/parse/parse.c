/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:24:49 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/26 11:12:49 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// no need
void	define_cmd(t_minishell **shell)
{
	t_node	*temp;

	temp = (*shell)->token_list;
	// temp->cmd_type = COMMAND;
	// temp = temp->next;
	while (temp)
	{
		if (temp->cmd_type == TOKEN_PIPE && temp->next)
		{
			temp->next->cmd_type = COMMAND;
			temp = temp->next;
		}
		temp = temp->next;
	}
}

int	parsing(t_minishell **shell)
{
	if (put_type(shell) == 1)
		return (1);
	define_cmd(shell);
	// print(shell);
	return (0);
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
		if (temp->next && (ft_strcmp(temp->node, "<") == 0))
		{
			temp->cmd_type = TOKEN_REDIRECT_IN;
			temp->next->cmd_type = FILEIN;
			temp = temp->next;
		}
		else if (temp->next && (ft_strcmp(temp->node, ">") == 0))
		{
			temp->cmd_type = TOKEN_REDIRECT_OUT;
			temp->next->cmd_type = FILEOUT;
			temp = temp->next;
		}
		else if (temp->next && (ft_strcmp(temp->node, ">>") == 0))
		{
			temp->cmd_type = TOKEN_APPEND;
			temp->next->cmd_type = FILEOUT;
			temp = temp->next;
		}
		else if (temp->next && (ft_strcmp(temp->node, "<<") == 0))
		{
			temp->cmd_type = TOKEN_HEREDOC;
			temp->next->cmd_type = FILEIN;
			temp = temp->next;
		}
		else if (ft_strcmp(temp->node, "|") == 0 && temp->next)
			temp->cmd_type = TOKEN_PIPE;
		else
			temp->cmd_type = TOKEN_ARG;
		temp = temp->next;
	}
	return (0);
}

t_node	*fix_redirection(t_node *list)
{
	t_node	*temp;
	t_node	*to_free;

	temp = list;
	while (temp)
	{
		if (temp->next && temp->next->next && ((ft_strcmp(temp->node, "<") == 0)
				&& (ft_strcmp(temp->next->node, "<") == 0)))
		{
			to_free = temp->next;
			temp->next = temp->next->next;
			free_node(to_free);
			free(temp->node);
			temp->node = ft_strdup("<<");
			if (!temp->node)
				return (NULL);
			temp = temp->next;
		}
		if (temp->next && temp->next->next && ((ft_strcmp(temp->node, ">") == 0)
				&& (ft_strcmp(temp->next->node, ">") == 0)))
		{
			to_free = temp->next;
			temp->next = temp->next->next;
			free_node(to_free);
			free(temp->node);
			temp->node = ft_strdup(">>");
			if (!temp->node)
				return (NULL);
			temp = temp->next;
		}
		temp = temp->next;
	}
	return (list);
}

//////////////////////////// delete
void	prt_list(t_minishell **shell)
{
	t_node	*current;

	current = NULL;
	printf("\n%s\n", "----------after-------------");
	current = (*shell)->token_list;
	while (current != NULL)
	{
		printf("%s", current->node);
		if (current->next != NULL)
			printf(" -> ");
		current = current->next;
	}
	printf(" -> NULL\n");
}

// void	print(t_minishell **shell)
// {
// 	// printf("\n**********cmd*********\n");
// 	t_cmd *tmp = (*(*shell)->cmd_list);
// 	int i;

// 	while (tmp)
// 	{
// 		i = 0;

// 		// Print command and args
// 		while (tmp->cmd_line && tmp->cmd_line[i])
// 		{
// 			printf("cmd_line : %s\n", tmp->cmd_line[i]);
// 			i++;
// 		}

// 		// Print redirections
// 		if (tmp->redirect)
// 		{
// 			if (tmp->append)
// 				printf("append : %s\n", tmp->redirect);
// 			else
// 				printf("redirect : %s\n", tmp->redirect);
// 		}
// 		if (tmp->file_out)
// 			printf("file_out : %s\n", tmp->file_out);
// 		if (tmp->file_in)
// 			printf("file_in  : %s\n", tmp->file_in);

// 		// Print pipe if exists
// 		if (tmp->pipe)
// 			printf("pipe     : %s\n", tmp->pipe);

// 		// Move to next command if there is one
// 		if (tmp->next)
// 			printf("NEXT CMD\n");

// 		tmp = tmp->next;
// 	}
// }