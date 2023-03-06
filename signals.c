/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:56:02 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/06 16:41:42 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int status)
{
	if (status == SIGINT)
	{
		g_exit_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");//err if fails
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	get_signals(void)
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
