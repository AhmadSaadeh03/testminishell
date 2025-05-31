/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:23:33 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/31 12:56:04 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_quit(int signal_number)
{
	g_signal = signal_number;
}

static void	handle_quit_signal(int quit_action)
{
	if (quit_action == 0)
		signal(SIGQUIT, SIG_DFL);
	else
		signal(SIGQUIT, SIG_IGN);
}

static void	handle_signals_helper(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, handle_ctrl_c_on_process);
		signal(SIGQUIT, handle_quit);
	}
	else if (mode == 2)
	{
		signal(SIGINT, handle_ctrl_c_on_process);
		handle_quit_signal(1);
	}
	else if (mode == 4)
	{
		signal(SIGINT, herdoc_signals);
		handle_quit_signal(1);
	}
}

void	handle_signals(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, handle_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		handle_signals_helper(mode);
}
