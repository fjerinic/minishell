/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:56:02 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/12 02:05:35 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ctrl_c(int status)
// {
// 	if (status == SIGINT)
// 	{
// 		g_exit_status = 130;
// 		ioctl(STDIN_FILENO, TIOCSTI, "\n");//err if fails
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 	}
// }

// void	get_signals(void)
// {
// 	signal(SIGINT, &ctrl_c);
// 	signal(SIGQUIT, SIG_IGN);
// }
