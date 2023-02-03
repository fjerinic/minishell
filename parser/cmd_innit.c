/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_innit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:48:59 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/03 12:39:28 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_cmds	*innit_cmd(char *input, int token_type)
// {
// 	t_cmds	*cmd;

// 	token = malloc(sizeof(t_tokens));
// 	if (!token)
// 	{
// 		return (NULL);
// 	}
// 	token->type = token_type;
// 	token->token = input;//malloc free
// 	token->next = NULL;
// 	return (token);
// }

// void	add_cmd(t_cmds **cmd_lst, t_cmds *cmd)
// {
// 	t_tokens	*first;

// 	first = *cmd_lst;
// 	if (*cmd_lst == NULL)
// 		*cmd_lst = cmd;
// 	else
// 	{
// 		while (first->next != NULL)
// 			first = first->next;
// 		first->next = cmd;
// 	}
// }
