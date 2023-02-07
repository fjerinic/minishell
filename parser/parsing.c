/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:48:59 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/07 21:15:32 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	innit_cmd_struct(t_tokens **token_lst, t_cmds **cmd_lst, char **envp)
{
	while (*token_lst != NULL)
	{	
		add_cmd(&(*cmd_lst), innit_cmd(envp, token_lst));
		if ((*token_lst) != NULL)
			*token_lst = (*token_lst)->next;	
	}
	return (1);
}


//count cmd amount
// 		//check for redir last etc.
// 		tmp = token_lst->next;
// 		//free token
// 		token_lst = tmp;