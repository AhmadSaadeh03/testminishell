/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:11:51 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/30 17:22:54 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	extract_var_name(char *str, t_handle_env *h)
{
	h->i++;
	h->var_start = h->i;
	while (str[h->i] && (ft_isalnum(str[h->i]) || str[h->i] == '_'))
		h->i++;
	h->var_name = ft_substr(str, h->var_start, h->i - h->var_start);
	if (!h->var_name)
		return (-1);
	return (0);
}

int	expand_var_value(t_handle_env *h, t_env *env_list)
{
	h->var_val = my_getenv(env_list, h->var_name);
	if (!h->in_double_quotes)
	{
		h->ptr = NULL;
		if (h->var_val)
			h->ptr = remove_all_spaces(h->var_val);
		if (h->ptr)
			h->new_str = ft_strjoin_free(h->new_str, h->ptr);
		else
			h->new_str = ft_strjoin_free(h->new_str, ft_strdup(""));
	}
	else
	{
		if (h->var_val)
			h->new_str = ft_strjoin_free(h->new_str, ft_strdup(h->var_val));
		else
			h->new_str = ft_strjoin_free(h->new_str, ft_strdup(""));
	}
	free(h->var_name);
	h->var_name = NULL;
	return (0);
}

int	handle_env_variable(char *str, t_handle_env *h, t_env *env_list)
{
	if (extract_var_name(str, h) == -1)
		return (-1);
	if (expand_var_value(h, env_list) == -1)
		return (-1);
	return (0);
}

void	handle_normal_char(char *str, t_handle_env *h)
{
	h->new_str = ft_strjoin_free(h->new_str, ft_substr(str, h->i, 1));
	h->i++;
}
