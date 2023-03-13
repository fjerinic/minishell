/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 11:10:15 by raweber           #+#    #+#             */
/*   Updated: 2023/03/13 01:11:01 by fjerinic         ###   ########.fr       */
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
	//clean_up(cmd_struct);
	free_cmd(cmd_struct);
	exit(g_exit_status);
}
