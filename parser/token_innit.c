/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_innit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:08:57 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/30 21:02:53 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*innit_token(char *input, int token_type)
{
	t_tokens	*token;

	token = malloc(sizeof(t_tokens));
	if (!token)
	{
		return (NULL);
	}
	token->type = token_type;
	token->token = input;//malloc free
	token->next = NULL;
	return (token);
}

t_tokens	*innit_token_word(char *input, int *i)
{
	t_tokens	*token;
	char		tmp;
	int			j;
	
	j = *i;
	if (input[j] == '"' || input[j] == '\'')
	{
		tmp = input[j++];
		while (input[j] != tmp)
			j++;
		token = innit_token(ft_substr(input, *i, j + 1 - *i) , WORD);//free
		*i = j;
	}
	else
	{
		while (input[j] != '\'' && input[j] != '"' && input[j] != '\n' && input[j] != '|'
				&& input[j] != '<' && input[j] != '>' && input[j] != ' ' && input[j])
			j++;
		token = innit_token(ft_substr(input, *i, j - *i) , WORD);//free
		*i = j - 1;
	}
	return (token);
}

void	add_token(t_tokens **token_lst, t_tokens *token)
{
	t_tokens	*first;

	first = *token_lst;
	if (*token_lst == NULL)
	{
		
		*token_lst = token;
	}
	else
	{
		while (first->next != NULL)
		{
			first = first->next;
		}
		first->next = token;
	}
}

t_tokens	*innit_redir(char *input, int *i, int type)
{
	t_tokens	*token;
	int			j;

	j = *i;
	if (type == REDIR_INPUT)
	{
		j++;
		*i = space_len(input, &j);
		word_len(input, &j);
		token = innit_token(ft_strjoin("<", ft_substr(input, *i, j - *i)), type);//free
	}
	else if (type == REDIR_OUTPUT)
	{
		j++;
		*i = space_len(input, &j);
		word_len(input, &j);
		token = innit_token(ft_strjoin(">", ft_substr(input, *i, j - *i)), type);//free
	}
	else if (type == HERE_DOC)
	{
		j += 2;
		*i = space_len(input, &j);
		word_len(input, &j);
		token = innit_token(ft_strjoin("<<", ft_substr(input, *i, j - *i)), type);//free
	}
	else
	{
		j += 2;
		*i = space_len(input, &j); 
		word_len(input, &j);
		token = innit_token(ft_strjoin(">>", ft_substr(input, *i, j - *i)), type);//free
	}
	if (input[j] == '"' || input[j] == '\'')
		*i = j;
	else
		*i = j - 1;	
	return (token);
}
