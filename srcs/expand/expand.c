/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:29:12 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/14 15:42:03 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand(t_minishell *shell, t_env **env_list)
{
	t_node	*temp;
	char	*new;
	char	*final;

	//t_env *env_list;
	//env_list = copy_env_to_list();
	temp = shell->token_list;
	while (temp)
	{
		if (ft_strcmp(temp->node, "export") == 0 && temp->next)
		{
			temp = temp->next;
			handle_export(temp->node, env_list);
			// print_env_list(&env_list);
		}
		if (temp->cmd_type == TOKEN_ARG)
		{
			// Step 1: Handle environment variables
			new = handle_env(temp->node, *env_list);
			if (!new)
				return ;
			// Step 2: Remove quotes
			final = ft_trim_quotes(new);
			free(new); // Free the intermediate string
			if (!final)
				return ;
			// Update the node with the final processed string
			free(temp->node);
			temp->node = final;
			if (temp->node)
				printf("%s\n", temp->node);
		}
		temp = temp->next;
	}
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

void	my_setenv(t_env **env_list, char *name, char *value)
{
	t_env	*temp;
	t_env	*new_node;

	temp = *env_list;
	// Check if the variable already exists
	while (temp)
	{
		if (ft_strcmp(temp->env_name, name) == 0)
		{
			printf("Updating existing variable: %s:  %s\n", name, value);
			free(temp->value);
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
	printf("Adding new variable: %s::    %s\n", name, value);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		printf("Memory allocation failed for new_node\n");
		return ;
	}
	new_node->env_name = ft_strdup(name);
	printf("name : %s\n", new_node->env_name);
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
		{
			perror("adding error");
			free(new_node->env_name);
			free(new_node);
			return ;
		}
		printf("vall : %s\n", new_node->value);

	}
	else
		new_node->value = NULL;
	new_node->next = *env_list;
	*env_list = new_node;
	printf("name : %s\n", (*env_list)->env_name);
	printf("val : %s\n", (*env_list)->value);


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
			printf("Removed variable: %s\n", name);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
	printf("Variable not found: %s\n", name);
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
