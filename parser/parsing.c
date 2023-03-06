/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:48:59 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/06 16:36:32 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_cmds *cmd)
{
	int		i;

	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->cmd_split)
	{
		i = 0;
		while (cmd->cmd_split[i])
			free(cmd->cmd_split[i++]);
		free(cmd->cmd_split);
	}
	free(cmd->err_file);
	free(cmd);
}

int		innit_cmd_struct(t_tokens **token_lst, t_cmds **cmd_lst, char **envp)
{
	t_tokens	*tmp_t;
	t_cmds		*tmp_c;

	while (*token_lst != NULL)
	{
		add_cmd(&(*cmd_lst), innit_cmd(envp, token_lst));
		if ((*token_lst) != NULL)
		{
			tmp_t = (*token_lst)->next;
			free((*token_lst)->token);
			free(*token_lst);
			*token_lst = tmp_t;
		}
	}
	if (g_exit_status == 130)
	{
		while (*cmd_lst != NULL)
		{
			tmp_c = (*cmd_lst)->next;
			free_cmd(*cmd_lst);
			*cmd_lst = tmp_c;
		}
		return (0);
	}
	return (1);
}

//int prev = 0
//before as arg for innit_cmd
//after add cmd if (prev == 0)
//prev++;
//or just prev++ all the time