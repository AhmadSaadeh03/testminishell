/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:30:05 by fghanem           #+#    #+#             */
/*   Updated: 2025/02/26 14:44:57 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

// this function to check that the qoutes are closed even number
int	closed_quotes(t_minishell *shell, char qoute)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (shell->name[i])
	{
		if (shell->name[i] == qoute)
			c++;
		i++;
	}
	if (c % 2 == 0)
		return (1);
	return (0);
}

static char	*ft_strremove(char *str, const char *remove)
{
	char	*result;
	char	*ptr;
	int		i;
	int		j;
	int		k;

	if (!str || !remove)
		return (NULL);
	result = (char *)malloc((ft_strlen(str) - ft_strlen(remove)) + 1);
	if (!result)
		return (NULL);
	ptr = str;
	i = 0;
	j = 0;
	k = 0;
	while (ptr[i])
	{
		while (ptr[i] != remove[k] && remove[k])
		{
			result[j++] = ptr[i];
			i++;
		}
		i++;
		k++;
	}
	result[j] = '\0';
	return (result);
}

void	split_quotes(t_minishell *shell, char operator)
{
	int		i;
	int		len;
	char	*temp;
	int		first;

	temp = NULL;
	i = 0;
	first = 0;
	len = 0;
	while (shell->name[i])
	{
		first = 0;
		if (shell->name[i] == operator)
		{
			first = i;
			i++;
			while (shell->name[i] != operator)
			{
				len++;
				i++;
			}
			if (shell->name[i] == operator)
			{
				len++;
				// i did a sub of the qouted part "hello world" and store it the struct shell->qouted
				shell->quoted = ft_substr(shell->name, first, len + 1);
				if (!shell->quoted)
					return ;
				temp = ft_strremove(shell->name, shell->quoted);
					// this function remove the qouted part from the name
				break ;
			}
			i++;
		}
		i++;
	}
	// printf("%s\n", shell->quoted);
	// printf("%s\n", temp);
	// free(shell->name);
	// shell->name = ft_strdup(temp);
	split_space(shell);
	// we need to store the shell->quoted in the node this way to split it is not very correct...
}
