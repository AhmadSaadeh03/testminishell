/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:49:32 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/26 16:05:47 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_all_spaces(char *str)
{
	int i = 0;
	int j = 0;
	char *ptr;
	ptr = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!ptr)
		return NULL;
	while (str[i])
	{
		while (str[i] == ' ' && str[i+1] == ' ')
			i++;
		ptr[j] = str[i];
		i++;
		j++;
	}
	ptr[j+1] = '\0';
	return ptr;
}
char	*handle_env(char *str, t_env *env_list)
{
	char	*new;
	int		i;
	int		in_single_quotes;
	int		in_double_quotes;
	//char	*var_start;
	char	*var_name;
	char	*var_val;
	in_single_quotes = 0;
	in_double_quotes = 0;
	new = ft_strdup("");
	i = 0;
    while (str[i])
    {
        if (str[i] == '\'') // Handle single quotes
        {
            if (!in_double_quotes)
                // Toggle single quotes only if not inside double quotes
                in_single_quotes = !in_single_quotes;
            else // If inside double quotes, preserve the single quote
                new = ft_strjoin_free(new, ft_substr(str, i, 1));
            i++; // Skip the single quote
        }
        else if (str[i] == '"') // Handle double quotes
        {
            if (!in_single_quotes)
                // Toggle double quotes only if not inside single quotes
                in_double_quotes = !in_double_quotes;
            else // If inside single quotes, preserve the double quote
                new = ft_strjoin_free(new, ft_substr(str, i, 1));
            i++; // Skip the double quote
        }
		else if (str[i] == '$' && !in_single_quotes && !ft_isalnum(str[i+1]) && str[i] != '_')//special char
		{
			i++;
			//char *old = NULL;
			// int temp;
			// temp = i;
			// i = 0;
			// while (str[i])
			// i++;
			// new = malloc(sizeof(char) * (i + 1));
			// i = temp;
			// int j = 0;
			// while (str[i])
			// {
			// 	new[j] = str[i];
			// 	j++;
			// 	i++;
			// }
			// new[j] = '\0';
			var_name = "$";
			new = ft_strjoin_free(new, ft_strdup(var_name));
		}
		else if (str[i] == '$' && !in_single_quotes && str[i+1] == '0')
		{
			i+=2;
			var_name = ft_strdup("./minishell");
			new = ft_strjoin_free(new, ft_strdup(var_name));
		}
		else if (str[i] == '$' && !in_single_quotes && (str[i+1] >= '1' && str[i+1] <= '9'))//numbers
			i += 2;
		else if (str[i] == '$' && !in_single_quotes && ft_isalpha(str[i+1]))
		{
				// int sign = i;
			i++; // Skip the '$'
			// if (in_double_quotes)
			// 	str = remove_all_spaces(str);
			int var_start = i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			var_name = ft_substr(str, var_start, i - var_start);
			char *ptr = NULL;
			if (!in_double_quotes)
			{
				var_val = my_getenv(env_list, var_name);
				free(var_name);
				if (var_val)
				{
					ptr = remove_all_spaces(var_val);
					if (ptr)
						new = ft_strjoin_free(new, ft_strdup(ptr));
					else
					{
						var_name = "";
						new = ft_strjoin_free(new, ft_strdup(var_name));
					}
				}
			}
			else
			{
				var_val = my_getenv(env_list, var_name);
				free(var_name);
				// if (in_double_quotes)
				// 	new = remove_all_spaces(str);
				if (var_val)
					new = ft_strjoin_free(new, ft_strdup(var_val));
					else // If variable is not found, keep it as-is
					{
					var_name = "";
					new = ft_strjoin_free(new, ft_strdup(var_name));
					}
			}
        	}
		// else if (str[i] == '$' && in_double_quotes &&  !in_single_quotes)
		// {
		// 		// int sign = i;
		// 	printf("hello");
		// 	i++; // Skip the '$'
		// 	// if (in_double_quotes)
		// 	// 	str = remove_all_spaces(str);
		// 	int var_start = i;
		// 	while (str[i] && ((ft_isalnum(str[i]) || str[i] == '_')))
		// 		i++;
		// 	var_name = ft_substr(str, var_start, i - var_start);
		// 	var_val = my_getenv(env_list, var_name);
		// 	char *ptr = remove_all_spaces(var_val);
		// 	// if (in_double_quotes)
		// 	// 	new = remove_all_spaces(str);
		// 	if (ptr)
		// 		new = ft_strjoin_free(new, ft_strdup(ptr));
		// 	     else // If variable is not found, keep it as-is
		// 	     {
		// 	        var_name = "";
		// 		new = ft_strjoin_free(new, ft_strdup(var_name));
		// 	     }
		// 	     free(var_name);
        	// }

        else // Handle literal characters
        {
            new = ft_strjoin_free(new, ft_substr(str, i, 1));
            i++;
        }
    }
    return (new);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*joined;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	ft_strcpy(joined, s1);
	ft_strcat(joined, s2);
	free(s1);
	free(s2);
	return (joined);
}

t_env	*copy_env_to_list(char **envp)
{
	t_env	*head;
	t_env	*tail;
	int		i;
	t_env	*new_node;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_env(envp[i]);
		if (!new_node)
		{
			i++;
			continue ;
		}
		if (!head)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		i++;
	}
	return (head);
}

t_env	*create_env(char *env_var)
{
	t_env	*node;
	char	*sign_equal;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	sign_equal = ft_strchr(env_var, '=');
	if (!sign_equal)
	{
		free(node);
		return (NULL);
	}
	*sign_equal = '\0';
	node->env_name = ft_strdup(env_var);
	node->value = ft_strdup(sign_equal + 1);
	*sign_equal = '=';
	node->next = NULL;
	return (node);
}
