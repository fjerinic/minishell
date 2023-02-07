/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:01:04 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/07 13:38:08 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*expander(t_tokens *token, char **envp)
{
	t_tokens	*token_lst;
	t_tokens	*tmp;
	int		i;
	char	*tmp_var;

	token_lst = NULL;
	while (token != NULL)
	{
		i = -1;
		tmp_var = NULL;
		while (token->token[++i] && token->token[0] != '\'' && token->type != PIPE)//redir included
		{
			if (token->token[i] == '$' && token->token[i + 1] != ' ' && token->token[i + 1] != '\0')
				tmp_var = get_var(token->token, envp);
		}
		if (tmp_var)
			add_token(&token_lst, innit_token(tmp_var, token->type));
		else
			add_token(&token_lst, innit_token(token->token, token->type));
		tmp = token->next;
		free(token);//free(content)
		token = tmp;
	}
	return (token_lst);
}