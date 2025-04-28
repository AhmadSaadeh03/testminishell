/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:36:10 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/28 16:01:14 by fghanem          ###   ########.fr       */
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
	free(array);
}

void free_minishell(t_minishell *shell)
{
	// free_array(shell->envps);
	free_cmd(shell->cmd_list);
	free_env_list(shell->env_list);
    free(shell);
}

void free_env_list(t_env **env_list)
{
	t_env *current;
	t_env *tmp;

	if (!env_list || !*env_list)
		return;
	current = *env_list;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->env_name);
		free(tmp->value);
		free(tmp);
	}
	*env_list = NULL;
}
