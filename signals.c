/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:56:02 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/17 18:16:24 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int status)
{
	if (status == SIGINT)
	{
		printf("abcdef\n");
	}
}

void	ctrl_d(int status)
{
	if (status == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_clear_history();
		rl_redisplay();
		rl_on_new_line();
		ft_putstr_fd("end\n", 1);
	}
}

// void	get_signals(void)
// {
// 	signal(SIGINT, &ctrl_c);
// 	signal(SIGQUIT, SIG_IGN);
// }
//SIG_IGN ignores signal
