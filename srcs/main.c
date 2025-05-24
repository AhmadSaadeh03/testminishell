/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/24 13:47:58 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
volatile sig_atomic_t s_signal = 0;

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
		handle_signals(0);
		if (s_signal == SIGINT)
		{
			 shell->last_exit = s_signal + 128;
			 s_signal = 0;
			continue;
		}
		shell->name = readline("👾Minihell> ");
		if ((shell->name) == NULL)
		{
			printf("exit\n");
			break;
		}
		if (shell->name[0] == '\0' || is_all_whitespace(shell->name))
		{
			free(shell->name);
			continue ;
		}
		add_history(shell->name);
		if (split(shell) == 1)
		{
			//free_exit(shell);
			free(shell->name);
			continue ;
		}
		if (cmd_filling(shell) == 1)
			return (1);
		 executing(shell);
		if (*(shell->cmd_list))
			free_cmd(*(shell->cmd_list));
		free(shell->cmd_list);
        if (shell->token_space)
			free_array(shell->token_space);
	}
    clear_history();
    free_env_list(*(shell->env_list));
	free(shell->env_list);
	free(shell);
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