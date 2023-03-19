/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 11:10:15 by raweber           #+#    #+#             */
/*   Updated: 2023/03/19 20:39:37 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_exit(t_cmds *cmd_struct)
{
	if (cmd_struct->cmd_split[1])
		g_exit_status = ft_atoi(cmd_struct->cmd_split[1]);
	else
		g_exit_status = 0;
	ft_printf("exit\n");
	if (g_exit_status == -2147483648)
	{
		ft_putstr_fd("bash: exit: numeric argument required\n", 2);
		g_exit_status = 255;
	}
	else if (cmd_struct->cmd_split[1] && cmd_struct->cmd_split[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		g_exit_status = 1;
		return ;
	}
	free_cmd_lst(cmd_struct);
	free_env(cmd_struct);
	exit(g_exit_status);
}
