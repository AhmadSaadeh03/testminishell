/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/04/13 12:48:48 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int arc, char **arv, char **envp)
{
	t_minishell	*shell;
	t_env		*env_list;

	shell = NULL;
	(void)arv;
	(void)arc;
	shell = init_shell(shell);
	if (!shell)
	{
		printf("ERROR:%s \n", "fail allocation of shell");
		exit(1);
	}
	env_list = NULL;
	env_list = copy_env_to_list(envp);
	while (1)
	{
		shell->name = readline("👾 Minihell> ");
		if (*(shell->name) == '\0')
		{
			free(shell->name);
			continue ;
		}
		add_history(shell->name);
		if (split(shell) == 1)
			free_and_exit(shell);
		// prt_list(&shell);
		expand(shell, env_list);
		cmd_filling(&shell);
		print(&shell);
		free(shell->name);
	}
	free_and_exit(shell);
	return (0);
}
