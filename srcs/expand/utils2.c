/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:13:47 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/30 17:22:15 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_special_char_dollar(t_handle_env *h)
{
	char	*var_name;

	var_name = "$";
	h->i++;
	h->new_str = ft_strjoin_free(h->new_str, ft_strdup(var_name));
}

int	handle_dollar_zero(t_handle_env *h)
{
	char	*var_name;

	h->i += 2;
	var_name = ft_strdup("./minishell");
	if (!var_name)
		return (-1);
	h->new_str = ft_strjoin_free(h->new_str, var_name);
	return (0);
}

void	handle_dollar_digit(t_handle_env *h)
{
	h->i += 2;
}

int	handle_dollar_cases(char *str, t_handle_env *h, t_env *env_list)
{
	if (!ft_isalnum(str[h->i + 1]) && str[h->i + 1] != '_')
		handle_special_char_dollar(h);
	else if (str[h->i + 1] == '0')
	{
		if (handle_dollar_zero(h) == -1)
			return (-1);
	}
	else if (str[h->i + 1] >= '1' && str[h->i + 1] <= '9')
		handle_dollar_digit(h);
	else if (ft_isalpha(str[h->i + 1]))
	{
		if (handle_env_variable(str, h, env_list) == -1)
			return (-1);
	}
	else
		handle_normal_char(str, h);
	return (0);
}
