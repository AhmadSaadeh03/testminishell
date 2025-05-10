/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/10 17:08:38 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int arc, char **arv, char **envp)
{
	t_minishell	*shell;

	(void)arv;
	(void)arc;
	shell = NULL;
	shell = init_shell(envp);
	if (!shell)
	{
		printf("ERROR:%s \n", "fail allocation of shell");
		exit(1);
	}
	while (1)
	{
		shell->name = readline("👾Minihell> ");
		// if (!shell->name)
			// continue ;
		if (shell->name[0] == '\0' || is_all_whitespace(shell->name))
		{
			free(shell->name);
			continue ;
		}
		add_history(shell->name);
		if (split(shell) == 1)
		{
			free_exit(shell);
			continue ;
		}
		// print_cmd_list(*(shell->cmd_list));
		executing(shell);
		if (*(shell->cmd_list))
			free_cmd(*(shell->cmd_list));
		free(shell->cmd_list);
        if (shell->token_space)
			free_array(shell->token_space);
	}
    clear_history();
    free_env_list(*(shell->env_list));
	return (0);
}

int	is_all_whitespace(const char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	print_cmd_list(t_cmd *head)
{
	int i = 0;
	while (head)
	{
		printf("------ Command #%d ------\n", i);
		if (head->cmd_line)
		{
			printf("Command Line: ");
			for (int j = 0; head->cmd_line[j]; j++)
				printf("'%s' ", head->cmd_line[j]);
			printf("\n");
		}
		else
			printf("Command Line: (null)\n");
		printf("heredoc_flag: %d\n", head->heredoc_flag);
		printf("redir_flag: %d\n", head->redir_flag);
		head = head->next;
		i++;
	}
}
