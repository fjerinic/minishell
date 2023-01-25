/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:11:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/25 11:42:59 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_tokens	*innit_token_word(char *input, int type_id, int *i)
{
	t_tokens	*token;
	int			j;
	
	j = *i;
	if (input[j++] == '"')
	{
		while (input[j] == '"')
			j++;
	}
	else if (input[j++] == '\'')
	{
		while (input[j] == '\'')
			j++;
	}
	else
	{
		while (input[j] != '\'' || input[j] != '"' || input[j] != '\n' || input[j] != '|'
				|| input[j] != '<' || input[j] != '>' || input[j] != ' ')
			j++;
	}
	token = innit_token(ft_substr(input, j, j - *i) , WORD);//free
	//maybe part of execution: make mod_substr which skips spaces if there are multiple
	*i = j;
	return (token);
}



t_tokens	*innit_token(char *input, int token_type)
{
	t_tokens	*token;

	token = malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	token->type = token_type;
	token->token = input;//malloc free
	token->next = NULL;
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
		{
			first = first->next;
		}
		first->next = token;
	}
}

int	lexer(t_tokens *token_lst, char *input)
{
	int			i;
	t_tokens	*token;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '|')
			token = innit_token(ft_strdup("|"), PIPE);
		else if (input[i] == '<' && input[i + 1] != '<')
			token = innit_token(ft_strdup("<"), REDIR_INPUT);
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			token = innit_token(ft_strdup("<<"), HERE_DOC);
			i++;
		}
		else if (input[i] == '>' && input[i + 1] != '>')	
			token = innit_token(ft_strdup(">"), REDIR_OUTPUT);
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			token = innit_token(ft_strdup(">>"), APPEND);
			i++;
		}
		else if (input[i] == '"' || input[i] == '\'' || input[i] != ' ')
			token = innit_token_word(input, WORD, &i);	//+word_len
		add_token(&token_lst, token);//free token_lst in parse
	}
}