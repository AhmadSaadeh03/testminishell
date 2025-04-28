/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:51:55 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/28 13:48:01 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_export(char *str, t_env **env_list)
{
    int		i;
    int		j;
    char	*before_equal;
    char	*after_equal;
    int     in_double_quote;
    int after_length;

    i = 0;
    j = 0;
    after_length = 0;
    while (str[i] && str[i] != '=')
        i++;
    before_equal = malloc((i + 1) * sizeof(char));
    if (!before_equal)
        return ;
    i = 0;
    while (str[i] && str[i] != '=')
    {
        before_equal[j] = str[i];
        i++;
        j++;
    }
    before_equal[j] = '\0';
    i++;
    j = 0;
    after_length = ft_strlen(str + i);
    after_equal = malloc((after_length) * sizeof(char) + 1);
    if (!after_equal)
    {
        free(before_equal);
        return ;
    }
    in_double_quote = 0;
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
            break;
        i++;
    }
    after_equal[j] = '\0';
    if (before_equal)
        my_setenv(env_list, before_equal, after_equal);
    free(after_equal);
    free(before_equal);
}
