/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/31 13:07:50 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static int	check_sig_and_prompt(t_minishell *shell)
{
	handle_signals(0);
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		return (1);
	}
	shell->name = readline("👾Minihell> ");
	if (g_signal == SIGINT)
		shell->last_exit = g_signal + 128;
	return (0);
}

static int	handle_empty_input(t_minishell *shell, int *status)
{
	if (shell->name == NULL)
	{
		printf("exit\n");
		*status = shell->last_exit;
		return (1);
	}
	return (0);
}

static void	run_and_cleanup(t_minishell *shell)
{
	add_history(shell->name);
	if (split(shell) == 1)
	{
		free(shell->name);
		return ;
	}
	if (cmd_filling(shell) == 1)
		return ;
	executing(shell);
	if (*(shell->cmd_list))
		free_cmd(*(shell->cmd_list));
	free(shell->cmd_list);
	if (shell->token_space)
		free_array(shell->token_space);
}

static int	handle_spaces(t_minishell *shell)
{
	if (shell->name[0] == '\0' || is_all_whitespace(shell->name))
	{
		free(shell->name);
		return (1);
	}
	return (0);
}

int	main(int arc, char **arv, char **envp)
{
	t_minishell	*shell;
	int			status;

	(void)arc;
	(void)arv;
	shell = NULL;
	status = 0;
	shell = init_shell(envp);
	if (!shell)
		exit(status);
	while (1)
	{
		if (check_sig_and_prompt(shell))
			continue ;
		if (handle_empty_input(shell, &status))
			break ;
		if (handle_spaces(shell))
			continue ;
		run_and_cleanup(shell);
	}
	clear_history();
	free_env_list(*(shell->env_list));
	free(shell->env_list);
	free(shell);
	return (status);
}
