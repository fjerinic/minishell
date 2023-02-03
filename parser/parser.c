/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:08:45 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/03 12:40:05 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse(char *input, char **envp)
{
	t_tokens	*token_lst = NULL;
	//t_cmds		*cmd_lst = NULL;

	if(!lex_error_check(input))
		return (0);
	token_lst = lexer(token_lst, input);
	token_lst = expander(token_lst, envp);
	// while (token_lst != NULL)
	// {
	// 	printf("token = %s & type = %i\n", token_lst->token, token_lst->type);
	// 	token_lst = token_lst->next;
	// }
	// if (innit_cmd_struct())
	// 	return (0);
	return (1);
}