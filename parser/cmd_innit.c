/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_innit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:48:59 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/08 16:02:27 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_tokens *token_lst)
{
	int			i;
	t_tokens	*tmp;

	i = 0;
	tmp = token_lst;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	cmd_split_loop(t_tokens **token_lst, t_cmds *cmd, char **envp, int i)
{
	t_tokens	*tmp;

	while (*token_lst != NULL && (*token_lst)->type != PIPE)
	{
		if (cmd->infile != -1 || (*token_lst)->type == DOC)
		{
			if ((*token_lst)->type == IN || (*token_lst)->type == OUT
				|| (*token_lst)->type == DOC || (*token_lst)->type == APP)
				redir_handler((*token_lst), cmd, envp);
			else if (((*token_lst)->type == WORD || (*token_lst)->type == SQ))
				cmd->cmd_split[i++] = (*token_lst)->token;
		}
		tmp = (*token_lst)->next;
		if (((*token_lst)->type != WORD && (*token_lst)->type != SQ)
			|| cmd->err != 0)
			free((*token_lst)->token);
		free(*token_lst);
		*token_lst = tmp;
		if (g_exit_status == 130)
		{
			free_token(*token_lst);
			*token_lst = NULL;
		}
	}
	return (i);
}

int	cmd_split_redir(t_tokens **token_lst, t_cmds *cmd, char **envp)
{
	int			i;

	i = count_args(*token_lst);
	if (i != 0)
	{
		cmd->cmd_split = malloc((i + 1) * sizeof(char *));
		if (!cmd->cmd_split)
			return (0);
	}
	return (cmd_split_loop(token_lst, cmd, envp, 0));
}

t_cmds	*innit_cmd(t_cmds *cmd, char **envp, t_tokens **token_lst, int prev)
{
	int	i;

	if (prev)
		cmd = cmd_struct(envp, prev);
	i = cmd_split_redir(token_lst, cmd, envp);
	if (i == 0)
	{
		if (cmd->cmd_split)
			free(cmd->cmd_split);
		cmd->cmd_split = NULL;
		cmd->cmd_path = NULL;
	}
	else
	{
		cmd->cmd_path = ft_find_path(envp, cmd->cmd_split[0], &cmd->err);
		cmd->cmd_split[i] = NULL;
	}
	return (cmd);
}

void	add_cmd(t_cmds **cmd_lst, t_cmds *cmd)
{
	t_cmds	*first;

	first = *cmd_lst;
	if (*cmd_lst == NULL)
	{
		*cmd_lst = cmd;
		(*cmd_lst)->next = NULL;
	}
	else
	{
		while (first->next != NULL)
			first = first->next;
		first->next = cmd;
		first->next->next = NULL;
	}
}
