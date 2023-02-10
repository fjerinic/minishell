/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:48:59 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/10 19:04:15 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	innit_cmd_struct(t_tokens **token_lst, t_cmds **cmd_lst, char **envp)
{
	(*cmd_lst) = innit_cmd(token_lst, (*cmd_lst));
	if ((*token_lst) != NULL)
			*token_lst = (*token_lst)->next;
	while (*token_lst != NULL)
	{
		add_cmd(&(*cmd_lst), innit_cmd(token_lst, innit_default_cmd(envp)));
		if ((*token_lst) != NULL)
			*token_lst = (*token_lst)->next;
	}
	return (1);
}


//count cmd amount
// 		tmp = token_lst->next;
// 		//free token
// 		token_lst = tmp;