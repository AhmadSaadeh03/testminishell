/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:23:33 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/15 19:59:45 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_ctrl_c(int signal_number) 
{
    if (signal_number)
    {
        printf("\n");
        rl_on_new_line();//cursor on new line
        rl_replace_line("", 0);
        rl_redisplay();
        s_signal = signal_number;
    }   
}

void handle_ctrl_c_on_process(int signal_number) 
{
       // write(STDOUT_FILENO, "\n", 1);
        s_signal = signal_number;
}

void    handle_after_child(int signal_number)
{
    write(STDOUT_FILENO, "\n", 1);
    s_signal = signal_number;
}

void    herdoc_signals(int signal_number)
{
    //write(STDOUT_FILENO, "\n", 1);
    s_signal = signal_number;
    exit (1);
}
void handle_signals(int mode)
{
    if (mode == 0)
    {
        signal(SIGINT,handle_ctrl_c);
        signal(SIGQUIT, SIG_IGN);
    }
    else if (mode == 1)
    {
        signal(SIGINT,handle_ctrl_c_on_process);
        if (signal(SIGQUIT,SIG_DFL))
            s_signal = SIGQUIT;
    }
    else if (mode == 2)
    {
        signal(SIGINT, handle_after_child);
        if (signal(SIGQUIT, SIG_IGN))
            s_signal = SIGQUIT;
    }
    else if (mode == 3)
    {
        signal(SIGINT,handle_ctrl_c_on_process);
         if (signal(SIGQUIT, SIG_IGN))
             s_signal = SIGQUIT;
    }
    else if (mode == 4)
    {
        signal(SIGINT,herdoc_signals);
         if (signal(SIGQUIT, SIG_IGN))
            s_signal = SIGQUIT;
    }
    // else if (mode == 2)
    // {
    //     signal(SIGINT,0);
    //     //signal(SIGQUIT,SIG_IGN);
    // }
    
}
