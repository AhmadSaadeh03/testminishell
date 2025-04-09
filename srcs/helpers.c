/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:42:51 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/09 13:32:51 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

char    *ft_trim_quotes(char *s1)
{
        int             start;
        int             end;

        if (!s1)
                return (NULL);
        start = 0;
        end = ft_strlen(s1) - 1;
        if (end < 0)
                return (ft_strdup(""));
        if ((s1[start] == '"' && s1[end] == '"') || (s1[start] == '\'' && s1[end] == '\''))
        {
                start++;
                end--;
        }
        return (ft_substr(s1, start, end - start + 1));
}

void restore_spaces(char **tokens)
{
        int i = 0, j;

        while (tokens[i])
        {
                j = 0;
                while (tokens[i][j])
                {
                        if (tokens[i][j] == '\a')
                                tokens[i][j] = ' ';
                        j++;
                }
                i++;
        }
}

char *replace_spaces_inside_quotes(const char *input)
{
        int i;
        int j;
        int inside_double;
        int inside_single;
        char *temp;

        i = 0;
        j = 0;
        inside_double = 0;
        inside_single = 0;
        temp = malloc(ft_strlen(input) + 1);
        if (!temp)
        return (NULL);
        while (input[i])
        {
                if (input[i] == '"' && !inside_double && !inside_single)
                        inside_double = 1;
                else if (input[i] == '"' && inside_double)
                        inside_double = 0;
                else if (input[i] == '\'' && !inside_single && !inside_double)
                        inside_single = 1;
                else if (input[i] == '\'' && inside_single)
                        inside_single = 0;
                if (input[i] == ' ' && (inside_single || inside_double))
                        temp[j++] = '\a';
                else
                        temp[j++] = input[i];
                i++;
        }
        temp[j] = '\0';
        return (temp);
}

char *space_before_op(char *str, int i, int *len)
{
        int new_len;
        char *new_str;

        new_len = *len + 1;
        new_str = malloc(new_len + 1);
        if (!new_str)
                return (NULL);
        ft_memcpy(new_str, str, i);
        new_str[i] = ' ';
        ft_memcpy(new_str + i + 1, str + i, *len - i + 1);
        free(str);
        *len = new_len;
        return (new_str);
}

char *space_after_op(char *str, int i, int *len)
{
        int new_len;

        new_len = *len + 1;
        char *new_str = malloc(new_len + 1);
        if (!new_str)
                return (NULL);
        ft_memcpy(new_str, str, i + 1);
        new_str[i + 1] = ' ';
        ft_memcpy(new_str + i + 2, str + i + 1, *len - i);
        free(str);
        *len = new_len;
        return (new_str);
}
