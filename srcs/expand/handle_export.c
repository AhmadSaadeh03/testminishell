/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:51:55 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/21 19:42:47 by asaadeh          ###   ########.fr       */
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
    
    i++; // Skip equal
    j = 0;
    int in_double_quote = 0;

    while (str[i])
    {
        if (str[i] == '"')
        {
            in_double_quote = !in_double_quote;
            i++;
            continue;
        }
       	if (in_double_quote || ft_isalnum(str[i]) || str[i] == ' ' 
	|| (!in_double_quote && !ft_isalnum(str[i])))
	{
   	 after_equal[j] = str[i];
    		j++;
	}
        else
        {
            break;
        }
        i++;
    }
    after_equal[j] = '\0';
    printf("var value :  %s\n", after_equal);

    if (before_equal)
        my_setenv(env_list, before_equal, after_equal);

    free(after_equal);
    free(before_equal);
}

// void    sort_env_list(t_env **env_list)
// {
//     int i;
//     int count;

//     i = 0;
//     count i = 0;
//     while()
// }
