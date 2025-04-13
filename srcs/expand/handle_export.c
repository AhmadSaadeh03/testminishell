/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:51:55 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/13 13:17:27 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_export(char *str, t_env **env_list)
{
	int		i;
	int		j;
	char	*before_equal;
	char	*after_equal;

	i = 0;
	j = 0;
	before_equal = ft_strdup("");
	after_equal = ft_strdup("");
	while (str[i] && str[i] != '=')
	{
		before_equal[j] = str[i];
		i++;
		j++;
	}
	before_equal[j] = '\0';
	printf("var name :  %s\n", before_equal);
	
	i++;
	j = 0;
	while (str[i])
	{
		after_equal[j] = str[i];
		i++;
		j++;
	}
	after_equal[j] = '\0';
	printf("var value :  %s\n", after_equal);
	if (after_equal && before_equal)
		my_setenv(env_list, before_equal, after_equal);
	free(after_equal);
	free(before_equal);
	// sort_env_list(env_list);
}

// void    sort_env_list(t_env **env_list)
// {
//     int i;
//     int count;

//     i = 0;
//     count i = 0;
//     while()
// }
