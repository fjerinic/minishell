/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:01:04 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/03 19:08:51 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*expander(t_tokens *token, char **envp)
{
	t_expan	e;

	e.token_lst = NULL;
	while (token != NULL)
	{
		e.i = -1;
		e.tmp_var = NULL;
		while (token->token[++e.i] && token->type != SQ && token->type != PIPE)
		{
			if (token->token[e.i] == '$' && token->token[e.i + 1] != ' '
				&& token->token[e.i + 1] != '\0')
			{
				e.tmp_var = get_var(token->token, envp);
				break ;
				free(token->token);
			}
		}
		if (e.tmp_var == NULL)
			e.tmp_var = token->token;
		add_token(&e.token_lst, innit_token(e.tmp_var, token->type));
		e.tmp = token->next;
		free(token);
		token = e.tmp;
	}
	return (e.token_lst);
}
