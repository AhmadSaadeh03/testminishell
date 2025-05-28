/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_mods.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:35:26 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/28 14:57:01 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_ctrl_c(int signal_number)
{
	if (signal_number)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = signal_number;
	}
}

void	handle_ctrl_c_on_process(int signal_number)
{
	g_signal = signal_number;
}

void	handle_after_child(int signal_number)
{
	//write(STDOUT_FILENO, "\n", 1);
	g_signal = signal_number;
}

void	herdoc_signals(int signal_number)
{
	write(STDOUT_FILENO, "\n", 1);
	g_signal = signal_number;
	close(0);
}

void    herdoc_signals_exit(int signal_number)
{
    write(STDOUT_FILENO, "\n", 1);
    g_signal = signal_number;
    exit(0);
}
