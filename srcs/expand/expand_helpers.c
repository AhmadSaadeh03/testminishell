/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:27:25 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/24 17:54:03 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_env_list_size(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

char	*join_env_pair(char *name, char *value)
{
	size_t	name_len;
	size_t	value_len;
	char	*joined;

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
	int		i;
	int		size;
	char	**env_array;
	char	*joined;

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

static int	update_env_value_if_exists(t_env *env_list, char *name, char *value)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (ft_strcmp(temp->env_name, name) == 0)
		{
			if (temp->value == NULL && value == NULL)
				return (1);
			if (temp->value && value == NULL)
				return (1);
			free(temp->value);
			temp->value = ft_strdup(value);
			if (!temp->value)
				return (1);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	my_setenv(t_env **env_list, char *name, char *value)
{
	t_env	*new_node;

	if (update_env_value_if_exists(*env_list, name, value))
		return ;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->env_name = ft_strdup(name);
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
	}
	else
		new_node->value = NULL;
	new_node->next = *env_list;
	*env_list = new_node;
}
