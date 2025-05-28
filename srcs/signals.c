/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:23:33 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/28 14:51:40 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	handle_ctrl_c(int signal_number)
// {
// 	if (signal_number)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		rl_on_new_line(); //cursor on new line
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		g_signal = signal_number;
// 	}
// }

// void	handle_ctrl_c_on_process(int signal_number)
// {
// 	g_signal = signal_number;
// }

// void	handle_after_child(int signal_number)
// {
// 	write(STDOUT_FILENO, "\n", 1);
// 	g_signal = signal_number;
// }

// void	herdoc_signals(int signal_number)
// {
// 	write(STDOUT_FILENO, "\n", 1);
// 	g_signal = signal_number;
// 	close(0);
// }
// void	handle_signals(int mode)
// {
// 	if (mode == 0)
// 	{
// 		signal(SIGINT, handle_ctrl_c);
// 		signal(SIGQUIT, SIG_IGN);
// 	}
// 	else if (mode == 1)
// 	{
// 		signal(SIGINT, handle_ctrl_c_on_process);
// 		if (signal(SIGQUIT, SIG_DFL))
// 			g_signal = SIGQUIT;
// 	}
// 	else if (mode == 2)
// 	{
// 		signal(SIGINT, handle_after_child);
// 		if (signal(SIGQUIT, SIG_IGN))
// 			g_signal = SIGQUIT;
// 	}
// 	else if (mode == 3)
// 	{
// 		signal(SIGINT, handle_ctrl_c_on_process);
// 		if (signal(SIGQUIT, SIG_IGN))
// 			g_signal = SIGQUIT;
// 	}
// 	else if (mode == 4)
// 	{
// 		signal(SIGINT, herdoc_signals);
// 		if (signal(SIGQUIT, SIG_IGN))
// 			g_signal = SIGQUIT;
// 	}
// 	else if (mode == 5)
// 	{
// 		signal(SIGINT, handle_ctrl_c_on_process);
// 		if (signal(SIGQUIT, SIG_IGN))
// 			g_signal = SIGQUIT;
// 	}
// }

static void	handle_quit_signal(int quit_action)
{
	if (quit_action == 0)
	{
		if (signal(SIGQUIT, SIG_DFL))
			g_signal = SIGQUIT;
	}
	else
	{
		if (signal(SIGQUIT, SIG_IGN))
			g_signal = SIGQUIT;
	}
}

static void	handle_signals_helper(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, handle_ctrl_c_on_process);
		handle_quit_signal(0);
	}
	else if (mode == 2)
	{
		signal(SIGINT, handle_after_child);
		handle_quit_signal(1);
	}
	else if (mode == 3)
	{
		signal(SIGINT, handle_ctrl_c_on_process);
		handle_quit_signal(1);
	}
	else if (mode == 4)
	{
		signal(SIGINT, herdoc_signals);
		handle_quit_signal(1);
	}
	else if (mode == 5)
	{
		signal(SIGINT, handle_ctrl_c_on_process);
		handle_quit_signal(1);
	}
	else if (mode == 6)
    {
        signal(SIGINT, herdoc_signals_exit);
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
