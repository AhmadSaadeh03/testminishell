/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:36:10 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/19 16:29:50 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_node(t_node *to_free)
{
	free(to_free->node);
	free(to_free);
}

void	free_token_space(char **token_space)
{
	int	i;

	i = 0;
	if (!token_space)
		return ;
	while (token_space[i])
		free(token_space[i++]);
	free(token_space);
}

void free_minishell(t_minishell *mini)
{
	if (!mini)
		return;
	free(mini->name);
	free_token_space(mini->token_space);
	if (mini->cmd_list && *mini->cmd_list)
		free_cmd_list(mini->cmd_list);
	if (mini->token_list)
		free_tokens(mini->token_list);
	if (mini->env_list && *mini->env_list)
		free_env_list(mini->env_list);
	free(mini->cmd_list);
	free(mini->env_list);
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
