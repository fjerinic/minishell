/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:11:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/03 16:14:25 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*lexer(t_tokens *token_lst, char *input)
{
	int			i;
	t_tokens	*token;

	token_lst = NULL;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '|')
			token = innit_token(ft_strdup("|"), PIPE);
		else if (input[i] == '<' && input[i + 1] != '<')
			token = innit_redir(input, &i, IN);
		else if (input[i] == '<' && input[i + 1] == '<')
			token = innit_redir(input, &i, DOC);
		else if (input[i] == '>' && input[i + 1] != '>')
			token = innit_redir(input, &i, OUT);
		else if (input[i] == '>' && input[i + 1] == '>')
			token = innit_redir(input, &i, APP);
		else if (input[i] != ' ')
			token = innit_token_word(input, &i);
		if (input[i] != ' ')
			add_token(&token_lst, token);
	}
	return (token_lst);
}
