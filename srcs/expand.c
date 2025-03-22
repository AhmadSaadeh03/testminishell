/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:29:12 by fghanem           #+#    #+#             */
/*   Updated: 2025/03/22 14:08:09 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

// char    *replace_var(char *first, char *wanted, char *replace)
// {
//     char    *pos;
//     int     new_len;
//     char    *expanded;
//     size_t len_bef;
//     size_t len_wanted;
//     size_t len_replace;
//     size_t len_after;

//     pos = ft_strstr(first, wanted);
//     if (!pos)
//         return(first);
//     len_bef = pos - first;
//     len_wanted = ft_strlen(wanted);
//     len_replace = ft_strlen(replace);
//     len_after = ft_strlen(pos + len_wanted);
//     new_len = ft_strlen(first) - len_wanted + len_replace + 1;
//     expanded = malloc(new_len);
//     if (!expanded)
//         return (NULL);
//     ft_memcpy(expanded, first, len_bef);
//     ft_memcpy(expanded + len_bef, replace, len_replace);
//     ft_memcpy(expanded + len_bef + len_replace, pos + len_wanted, len_after);
//     expanded[new_len - 1] = '\0';
//     return (expanded);
// }

// char    *expand_args(char   *var)
// {
//     char    *expanded;
//     char    *exit_status_str;
//     char    *temp;
//     char    *var_name;
//     char    *var_value;

//     expanded = ft_strdup(var);
//     if(!expanded)
//         return(NULL);
//     expanded = replace_var(expanded, "$$", ft_itoa(getpid()));
//     exit_status_str = ft_itoa(0);
//     temp = replace_var(expanded, "$?", exit_status_str);
//     free(expanded);
//     expanded = temp;
//     if (expanded[0] == '$' && expanded[1] != '?' && expanded[1] != '$')
//     {
//         var_name = expanded + 1;
//         var_value = getenv(var_name);
//         if (var_value)
//         {
//             temp = ft_strdup(var_value);
//             free(expanded);
//             expanded = temp;
//         }
//         else
//         {
//             free(expanded);
//             expanded = ft_strdup("");
//         }
//     }
//     return(expanded);
// }

// void    expanding(t_minishell **shell)
// {
//     char    **tokens;
//     char    *expanded;
//     int     i;

//     tokens = (*(*shell)->cmd_list)->args;
//     i = 0;
//     while (tokens[i])
//     {
//         // if (tokens[i][1] != 39)
//         // {
//         if (ft_strcmp(tokens[i], "echo") != 0)
//         {
//             expanded = expand_args(tokens[i]);
//             free(tokens[i]);
//             tokens[i] = expanded;
//         }
//         i++;
//     }
//     print_expanded_args(shell);
// }

// void print_expanded_args(t_minishell **shell)
// {
//     char **tokens;
//     int i;

//     // Get the tokens (arguments) from the command list
//     tokens = (*(*shell)->cmd_list)->args;

//     // Check if tokens are NULL
//     if (!tokens)
//     {
//         printf("No arguments to print.\n");
//         return;
//     }

//     // Print each expanded argument
//     i = 0;
//     while (tokens[i])
//     {
//         printf("Expanded Argument %d: '%s'\n", i + 1, tokens[i]);
//         i++;
//     }
// }