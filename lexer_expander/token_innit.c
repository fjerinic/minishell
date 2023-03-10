/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_innit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:08:57 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/10 21:44:45 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*innit_token(char *input, int token_type)
{
	t_tokens	*token;

	token = malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	token->type = token_type;
	token->token = input;
	token->next = NULL;
	return (token);
}

t_tokens	*innit_token_word(char *input, int *i)
{
	t_innit_tw	t;

	t.j = *i;
	if (input[t.j] == '"' || input[t.j] == '\'')
	{
		t.tmp = input[t.j++];
		while (input[t.j] != t.tmp)
			t.j++;
		t.token = innit_token(ft_substr(input, *i + 1, t.j - *i - 1), WORD);
		if (input[*i] == '\'')
			t.token->type = SQ;
		*i = t.j;
	}
	else
	{
		while (input[t.j] != '\'' && input[t.j] != '"' && input[t.j] != '\n'
			&& input[t.j] != '|' && input[t.j] != '<' && input[t.j] != '>'
			&& input[t.j] != ' ' && input[t.j])
			t.j++;
		t.token = innit_token(ft_substr(input, *i, t.j - *i), WORD);
		if (ft_strchr(t.token->token, '=') && ft_isalpha(t.token->token[0]))
			t.token->type = EQUAL;
		*i = t.j - 1;
	}
	return (t.token);
}

t_tokens	*innit_redir(char *input, int *i, int type)
{
	t_tokens	*token;
	int			j;

	j = *i;
	if (type == IN || type == OUT)
	{
		j++;
		*i = space_len(input, &j);
		word_len(input, &j);
		token = innit_token(ft_substr(input, *i, j - *i), type);
	}
	else
	{
		j += 2;
		*i = space_len(input, &j);
		word_len(input, &j);
		token = innit_token(ft_substr(input, *i, j - *i), type);
	}
	if (input[j] == '"' || input[j] == '\'')
		*i = j;
	else
		*i = j - 1;
	return (token);
}

void	add_token(t_tokens **token_lst, t_tokens *token)
{
	t_tokens	*first;

	first = *token_lst;
	if (*token_lst == NULL)
		*token_lst = token;
	else
	{
		while (first->next != NULL)
			first = first->next;
		first->next = token;
	}
}
