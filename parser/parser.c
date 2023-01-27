/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:08:45 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/27 18:41:57 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse(char *input, char **envp)
{
	t_tokens	*token_lst = NULL;

	if(!lex_error_check(input))
		return (0);
	token_lst = lexer(token_lst, input);
	token_lst = expander(token_lst, envp);
	
	
	// if(lexer(&token_lst, input))
	// 	error_msg();
	// while (&token_lst != NULL) //token_lst != NULL
	// {
		
	// }
	return (1);
}