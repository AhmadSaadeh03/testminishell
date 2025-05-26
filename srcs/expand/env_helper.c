/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:52:47 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/25 15:56:25 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_all_spaces(char *str)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = NULL;
	ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		while (str[i] == ' ' && str[i + 1] == ' ')
			i++;
		ptr[j] = str[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*joined;

	len1 = 0;
	len2 = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc((len1 + len2) + 1);
	if (!joined)
		return (NULL);
	ft_strcpy(joined, s1);
	ft_strcat(joined, s2);
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (joined);
}

t_env	*copy_env_to_list(char **envp)
{
	t_env	*head;
	t_env	*tail;
	int		i;
	t_env	*new_node;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_env(envp[i]);
		if (!new_node)
		{
			i++;
			continue ;
		}
		if (!head)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		i++;
	}
	return (head);
}

t_env	*create_env(char *env_var)
{
	t_env	*node;
	char	*sign_equal;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	sign_equal = ft_strchr(env_var, '=');
	if (!sign_equal)
	{
		free(node);
		return (NULL);
	}
	*sign_equal = '\0';
	node->env_name = ft_strdup(env_var);
	node->value = ft_strdup(sign_equal + 1);
	*sign_equal = '=';
	node->next = NULL;
	return (node);
}
