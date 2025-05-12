/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:29:12 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/12 15:42:49 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand(t_minishell *shell)
{
	t_node	*temp;
	char	*new;
	char	*final;

	temp = shell->token_list;
	while (temp)
	{
		if (temp->cmd_type == TOKEN_ARG)
		{
			new = handle_env(temp->node, (*shell->env_list));
			if (!new)
				return (1);
			final = ft_trim_quotes(new);
			if (!final)
			{
				free(new);
				return (1);
			}
			free(new);
			free(temp->node);
			temp->node = final;
		}
		temp = temp->next;
	}
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
			return ;
		}
		prev = temp;
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
