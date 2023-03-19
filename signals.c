/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:56:02 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/19 21:52:05 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int status)
{
	if (status == SIGINT)
	{
		g_exit_status = 130;
		if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
			strerror(errno);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	ctrl_c_child(int status)
{
	if (status == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
	}
	if (status == SIGQUIT)
	{
		g_exit_status = 24;
		ft_putstr_fd("Quit\n", 1);
	}
}

void	get_signals(void)
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	get_signals_child(void)
{
	signal(SIGINT, &ctrl_c_child);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_child_active(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
