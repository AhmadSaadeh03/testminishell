/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:29:12 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/21 14:40:14 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand(t_minishell *shell)
{
	t_node	*temp;
	char	*new;
	char	*final;

	//t_env *env_list;
	//env_list = copy_env_to_list();
	temp = shell->token_list;
	while (temp)
	{
		// if (ft_strcmp(temp->node, "export") == 0 && temp->next)
		// {
		// 	temp = temp->next;
		// 	handle_export(temp->node, shell->env_list);
		// 	// print_env_list(&env_list);
		// }
		if (temp->cmd_type == TOKEN_ARG)
		{
			// Step 1: Handle environment variables
			new = handle_env(temp->node, (*shell->env_list));
			if (!new)
				return (1);
			// Step 2: Remove quotes
			final = ft_trim_quotes(new);
			free(new); // Free the intermediate string
			if (!final)
				return (1);
			// Update the node with the final processed string
			free(temp->node);
			temp->node = final;
		}
		temp = temp->next;
	}
	shell->envps = copy_env_list_to_array((*shell->env_list));
	return (0);
}

void	my_unsetenv(t_env **env_list, char *name)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env_list;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->env_name, name) == 0)
		{
			if (prev == NULL)
				*env_list = temp->next;
			else
				prev->next = temp->next;
			free(temp->env_name);
			free(temp->value);
			free(temp);
			// printf("Removed variable: %s\n", name);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
	// printf("Variable not found: %s\n", name);
}

char	*my_getenv(t_env *env_list, char *name)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (ft_strcmp(temp->env_name, name) == 0)
		{
			return (temp->value);
		}
		temp = temp->next;
	}
	return (NULL);
}

/// deletee

void	print_env_list(t_env **env_list)
{
	t_env	*env;

	env = (*env_list);
	while (env)
	{
		printf("%s=%s\n", env->env_name, env->value);
		env = env->next;
	}
}
