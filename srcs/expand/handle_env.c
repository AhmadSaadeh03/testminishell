/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:49:32 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/30 17:15:26 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_single_quote(char *str, t_handle_env *h)
{
	if (!h->in_double_quotes)
		h->in_single_quotes = !h->in_single_quotes;
	else
		h->new_str = ft_strjoin_free(h->new_str, ft_substr(str, h->i, 1));
	h->i++;
}

void	handle_double_quote(char *str, t_handle_env *h)
{
	if (!h->in_single_quotes)
		h->in_double_quotes = !h->in_double_quotes;
	else
		h->new_str = ft_strjoin_free(h->new_str, ft_substr(str, h->i, 1));
	h->i++;
}

int	process_char(char *str, t_handle_env *h, t_env *env_list)
{
	if (str[h->i] == '\'')
		handle_single_quote(str, h);
	else if (str[h->i] == '"')
		handle_double_quote(str, h);
	else if (str[h->i] == '$' && !h->in_single_quotes)
	{
		if (handle_dollar_cases(str, h, env_list) == -1)
			return (-1);
	}
	else
		handle_normal_char(str, h);
	return (0);
}

char	*handle_env(char *str, t_env *env_list)
{
	t_handle_env	h;

	h.i = 0;
	h.in_single_quotes = 0;
	h.in_double_quotes = 0;
	h.var_name = NULL;
	h.var_val = NULL;
	h.var_start = 0;
	h.ptr = NULL;
	h.new_str = ft_strdup("");
	if (!h.new_str)
		return (NULL);
	while (str[h.i])
	{
		if (process_char(str, &h, env_list) == -1)
		{
			free(h.new_str);
			return (NULL);
		}
	}
	return (h.new_str);
}
