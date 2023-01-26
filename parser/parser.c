/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:08:45 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/26 19:51:29 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse(char *input)
{
	t_tokens	*token_lst = NULL;
	

	if(!lex_error_check(input))
		return (0);
	token_lst = lexer(token_lst, input);
	// if(lexer(&token_lst, input))
	// 	error_msg();
	// while (&token_lst != NULL) //token_lst != NULL
	// {
		
	// }
	return (1);
}