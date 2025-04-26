/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:27:25 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/26 11:45:53 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_env_list_size(t_env *env_list)
{
    int count = 0;
    while (env_list)
    {
        count++;
        env_list = env_list->next;
    }
    return count;
}

char	*join_env_pair(char *name, char *value)
{
	size_t name_len;
	size_t value_len;
	char *joined;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	joined = malloc(name_len + value_len + 2);
	if (!joined)
		return (NULL);
	ft_strcpy(joined, name);
	joined[name_len] = '=';
	ft_strcpy(joined + name_len + 1, value);
	return (joined);
}

char	**copy_env_list_to_array(t_env *env_list)
{
	int i;
	int size;
	char **env_array;
	char *joined;

	env_array = NULL;
	i = 0;
	size = get_env_list_size(env_list);
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	while (env_list)
	{
		if (env_list->env_name && env_list->value)
		{
			joined = join_env_pair(env_list->env_name, env_list->value);
			if (!joined)
				break ;
			env_array[i++] = joined;
		}
		env_list = env_list->next;
	}
	env_array[i] = NULL;
	return (env_array);
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
