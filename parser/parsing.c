/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:48:59 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/22 15:02:43 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_cmds *cmd)
{
	int		i;
	t_cmds	*tmp;

	while (cmd != NULL)
	{
		tmp = cmd->next;
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		if (cmd->cmd_split)
		{
			i = 0;
			while (cmd->cmd_split[i])
				free(cmd->cmd_split[i++]);
			free(cmd->cmd_split);
		}
		free(cmd);
		cmd = tmp;
	}
}

int	innit_cmd_struct(t_tokens **token_lst, t_cmds **cmd_lst, char **envp)
{
	t_tokens	*tmp;
	
	while (*token_lst != NULL)
	{	
		add_cmd(&(*cmd_lst), innit_cmd(envp, token_lst));
		if ((*token_lst) != NULL)
		{
			tmp = (*token_lst)->next;
			free((*token_lst)->token);
			free(*token_lst);
			*token_lst = tmp;
		}
	}
	if (exit_status == 130)
		free_cmd(*cmd_lst);
	return (1);
}


//count cmd amount