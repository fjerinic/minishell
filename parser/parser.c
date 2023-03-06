/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:08:45 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/06 12:34:12 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmds	*parse(char *input, char **envp)
{
	t_tokens	*token_lst;
	t_cmds		*cmd_lst;

	token_lst = NULL;
	cmd_lst = NULL;
	if (!lex_error_check(input))
		return (0);
	token_lst = lexer(token_lst, input);
	token_lst = expander(token_lst, envp);
	g_exit_status = 0;
	if (innit_cmd_struct(&token_lst, &cmd_lst, envp) != 1)
		return (NULL);
	return (cmd_lst);
}
