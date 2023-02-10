/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_innit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:48:59 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/10 19:05:45 by jkroger          ###   ########.fr       */
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


t_cmds	*innit_cmd(t_tokens **token_lst, t_cmds *cmd)
{
	int		i;
	int 	j;
	//t_cmds	*cmd;

	i = count_args(*token_lst);
	if (i != 0)
		cmd->cmd_split = malloc((i + 1) * sizeof(char *));
	if (!cmd->cmd_split)
		return (0);
	j = 0;
	while (*token_lst != NULL && (*token_lst)->type != PIPE)
	{
		if ((*token_lst)->type == REDIR_INPUT || (*token_lst)->type == REDIR_OUTPUT 
		|| (*token_lst)->type == HERE_DOC || (*token_lst)->type == APPEND)
			redir_handler((*token_lst), cmd);
		else if ((*token_lst)->type == WORD)
			cmd->cmd_split[j++] = (*token_lst)->token;//ft_strdup((*token_lst)->token)
		(*token_lst) = (*token_lst)->next;
	}
	cmd->cmd_split[j] = NULL;
	cmd->cmd_path = ft_find_path(cmd->env, cmd->cmd_split[0]);


	// if (!(*cmd_lst)->cmd_path)
	// 	return(0); error
	// (*cmd_lst)->cmd_amount = 0;

	cmd->next = NULL;
	return (cmd);
}

void	add_cmd(t_cmds **cmd_lst, t_cmds *cmd)
{
	t_cmds	*first;

	first = *cmd_lst;
	if (*cmd_lst == NULL)
		*cmd_lst = cmd;
	else
	{
		while (first->next != NULL)
			first = first->next;
		first->next = cmd;
	}
}
