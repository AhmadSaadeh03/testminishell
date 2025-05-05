/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:36:10 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/03 15:42:23 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_node(t_node *to_free)
{
	free(to_free->node);
	free(to_free);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	// free(array);
}

void	free_start(t_minishell *shell)
{
	if (shell->cmd_list)
	{
		// free_cmd_Aaa(*shell->cmd_list);
		// free(shell->cmd_list);
		shell->cmd_list = NULL;
	}
	if (shell->token_space)
	{
		free_array(shell->token_space);
		shell->token_space = NULL;
	}
	// free(shell->last_arg);
	// free(shell->print_last_arg);
}

void free_minishell(t_minishell *shell)
{
	free_array(shell->envps);
	// free_cmd_Aaa(*(shell->cmd_list));
	// free(shell->cmd_list);
	free_env_list(*(shell->env_list));
	free(shell->env_list);
	free(shell->last_arg);
	free(shell->print_last_arg);
	if (shell->token_space)
		free_array(shell->token_space);
    // free(shell);
}

void free_env_list(t_env *head)
{
	t_env	*temp;

    while (head)
    {
        temp = head;
        head = head->next;
        if (temp->env_name)
            free(temp->env_name);
        if (temp->value)
            free(temp->value);
        free(temp);
    }
}
