/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:58:14 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/26 13:56:26 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int ft_get_last_char(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i]== '=')
            return 0;
        i++;
    }
    return 1;
}
void    ft_export(t_minishell *shell, char **cmd_line)
{
    int i;

    i = 1;
    if (cmd_line[i] == NULL)
    {
        sort_export_list_and_print(shell->env_list);
        return ;
    }
    else
    {
        while (cmd_line[i])
        {
            if (ft_get_last_char(cmd_line[i]) == 0)
            {
                // printf("cmd line is %s\n",cmd_line[i]);
                handle_export(cmd_line[i], shell->env_list);
                // if(!cmd->cmd_line[i+1])
                //     break;
            }
            else
                break;
            i++;
        }
    }
}

void    sort_export_list_and_print(t_env **env_list)
{
    t_env   *sorted_list;
    t_env   *current;

    sorted_list = NULL;
    current = (*env_list);
    sort_list(&current);
    sorted_list = current;
    while (sorted_list)
    {
        if (sorted_list->value)
            printf("declare -x %s=\"%s\"\n", sorted_list->env_name, sorted_list->value);
        else
            printf("declare -x %s\n", sorted_list->env_name);
        sorted_list = sorted_list->next;
    }
    free_env_list(&sorted_list);
}

void sort_list(t_env **env_list)
{
	t_env *ptr;
	int swapped;

	if (!env_list || !(*env_list))
		return;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = *env_list;
		while (ptr && ptr->next)
		{
			if (ft_strcmp(ptr->env_name, ptr->next->env_name) > 0)
			{
				swap_nodes(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
    }
}

void    swap_nodes(t_env *a, t_env *b)
{
    char *tmp_name;
    char *tmp_value;
    
    tmp_value = a->value;
    tmp_name = a->env_name;
    a->env_name = b->env_name;
    a->value = b->value;
    b->env_name = tmp_name;
    b->value = tmp_value;
}
