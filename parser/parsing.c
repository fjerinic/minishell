/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:48:59 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/08 19:12:33 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_cmds *cmd, int i)
{
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->cmd_split)
	{
		while (cmd->cmd_split[i])
			free(cmd->cmd_split[i++]);
		free(cmd->cmd_split);
	}
	free(cmd->err_file);
	if (cmd->prev != 0)
	{
		i = 0;
		while (cmd->env[i])
			free(cmd->env[i++]);
		free(cmd->env);
		free(cmd);
	}
	else
	{
		cmd->infile = 0;
		cmd->outfile = 1;
		cmd->err = 0;
		cmd->err_file = NULL;
		cmd->cmd_split = NULL;
	}
}

void	free_cmd_lst(t_cmds *cmd_lst)
{
	t_cmds	*tmp_c;

	while (cmd_lst != NULL)
	{
		tmp_c = cmd_lst->next;
		free_cmd(cmd_lst, 0);
		cmd_lst = tmp_c;
	}
}

int	innit_cmd_struct(t_tokens **token_lst, t_cmds **cmd_lst, char **envp)
{
	t_innit_cmd_struct	i;

	i.prev = 0;
	i.cmd = NULL;
	while (*token_lst != NULL)
	{
		if (i.prev == 0)
			add_cmd(&(*cmd_lst), innit_cmd(*cmd_lst, envp, token_lst, i.prev));
		else
			add_cmd(&(*cmd_lst), innit_cmd(i.cmd, envp, token_lst, i.prev));
		if ((*token_lst) != NULL)
		{
			i.tmp_t = (*token_lst)->next;
			free((*token_lst)->token);
			free(*token_lst);
			*token_lst = i.tmp_t;
		}
		i.prev++;
	}
	if (g_exit_status == 130)
	{
		free_cmd_lst(*cmd_lst);
		return (0);
	}
	return (1);
}
