/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:49:32 by fghanem           #+#    #+#             */
/*   Updated: 2025/05/29 14:39:05 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*handle_env(char *str, t_env *env_list)
// {
// 	char	*new;
// 	int		i;
// 	int		in_single_quotes;
// 	int		in_double_quotes;
// 	char	*var_name;
// 	char	*var_val;
// 	int		var_start;
// 	char	*ptr;

// 	in_single_quotes = 0;
// 	in_double_quotes = 0;
// 	var_val = NULL;
// 	var_name = NULL;
// 	new = ft_strdup("");
// 	if (!new)
// 		return (NULL);
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 		{
// 			if (!in_double_quotes)
// 				in_single_quotes = !in_single_quotes;
// 			else
// 				new = ft_strjoin_free(new, ft_substr(str, i, 1));
// 			i++;
// 		}
// 		else if (str[i] == '"')
// 		{
// 			if (!in_single_quotes)
// 				in_double_quotes = !in_double_quotes;
// 			else
// 				new = ft_strjoin_free(new, ft_substr(str, i, 1));
// 			i++;
// 		}
// 		else if (str[i] == '$' && !in_single_quotes && !ft_isalnum(str[i + 1])
// 				&& str[i] != '_') //special char
// 		{
// 			i++;
// 			var_name = "$";
// 			new = ft_strjoin_free(new, ft_strdup(var_name));
// 		}
// 		else if (str[i] == '$' && !in_single_quotes && str[i + 1] == '0')
// 		{
// 			i += 2;
// 			var_name = ft_strdup("./minishell");
// 			if (!var_name)
// 				return (NULL);
// 			new = ft_strjoin_free(new, var_name);
// 		}
// 		else if (str[i] == '$' && !in_single_quotes && (str[i + 1] >= '1'
// 					&& str[i + 1] <= '9')) //numbers
// 			i += 2;
// 		else if (str[i] == '$' && !in_single_quotes && ft_isalpha(str[i + 1]))
// 		{
// 			i++;
// 			var_start = i;
// 			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 				i++;
// 			var_name = ft_substr(str, var_start, i - var_start);
// 			if (!var_name)
// 				return (NULL);
// 			ptr = NULL;
// 			if (!in_double_quotes)
// 			{
// 				var_val = my_getenv(env_list, var_name);
// 				free(var_name);
// 				if (var_val)
// 				{
// 					ptr = remove_all_spaces(var_val);
// 					if (ptr)
// 						new = ft_strjoin_free(new, ptr);
// 					else
// 					{
// 						new = ft_strjoin_free(new, "");
// 					}
// 				}
// 			}
// 			else
// 			{
// 				var_val = my_getenv(env_list, var_name);
// 				free(var_name);
// 				if (var_val)
// 					new = ft_strjoin_free(new, ft_strdup(var_val));
// 				else
// 					new = ft_strjoin_free(new, ft_strdup(""));
// 			}
// 		}
// 		else
// 		{
// 			new = ft_strjoin_free(new, ft_substr(str, i, 1));
// 			i++;
// 		}
// 	}
// 	return (new);
// }

