/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 23:03:13 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/12 23:03:59 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_var(t_cmds *cmd)
{
	int i;
	
	if (!cmd->cmd_split)
		return (cmd->var_lst);
	if (cmd->prev == 0 && cmd->next == NULL && ft_strchr(cmd->cmd_split[0], '=') && ft_isalpha(cmd->cmd_split[0][0]))
	{
		i = -1; 
		while (cmd->cmd_split[++i])
			cmd->var_lst = add_env(cmd->var_lst, cmd->cmd_split[i]);
	}
	return (cmd->var_lst);
}