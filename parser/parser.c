/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:08:45 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/09 12:53:45 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmds	*parse(t_cmds *cmd_lst, char *input, char **envp)
{
	t_tokens	*token_lst;

	token_lst = NULL;
	if (!lex_error_check(input))
	{
		cmd_lst->err = -2;
		return (cmd_lst);
	}
	token_lst = lexer(token_lst, input);
	token_lst = expander(token_lst, envp);
	g_exit_status = 0;
	if (innit_cmd_struct(&token_lst, &cmd_lst, envp) != 1)
		cmd_lst->err = -2;
	return (cmd_lst);
}
