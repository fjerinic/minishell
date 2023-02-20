/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pre_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:45:26 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/20 20:01:48 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_spaces(char *input)
{
	int i;

	i = -1;
	while (input[++i] != '\0')
	{
		if (input[i] != ' ')
			return (1);
	}
	return (0);//nothing happens
}

int	check_unclosed_quotes(char *input)
{
	int	i;
	int	j;
	
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			j = i + 1;		
			while (input[j] && input[j] != input[i])
				j++;
			if (!input[j])
			{
				lex_error("uclosed quotes");
				return (0);
			}
			i = j;
		}
	}
	return (1);
}

int	check_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '|')
	{
		if (input[i + 1] == '|')
			lex_error("||");
		else
			lex_error("|");
		return (0);
	}
	while (input[i++])
	{
		if (input[i] == '\'' || input[i] == '"')
			quote_len(&input[i], &i);
		if (input[i] == '|')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '|' || input[i] == '\0')
			{
				lex_error("|");
				return (0);		
			}
		}
	}
	return (1);
}

int	check_redir(char *input)//also pipes checking
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '"')
			quote_len(&input[i], &i);
		if (input[i] == '<')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i - 1] == ' ' && input[i] == '<')
			{
				lex_error("<");
				return (0);
			}
			if (input[i] == '<')
				i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '>' || input[i] == '\0' || input[i] == '<' || input[i] == '|')
			{
				if (input[i] == '\0' || input[i] == '>')
					lex_error("newline");
				else if (input[i] == '<')
					lex_error("<");
				else if (input[i] == '>' && input[i] == '>')
					lex_error("<<");
				else
					lex_error("|");
				return (0);
			}
		}
		else if (input[i] == '>')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i - 1] == ' ' && input[i] == '>')
			{
				lex_error(">");
				return (0);
			}
			if (input[i] == '>')
				i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '<' || input[i] == '\0' || input[i] == '>' || input[i] == '|')
			{
				if (input[i] == '\0')
					lex_error("newline");
				else if (input[i] == '>')
					lex_error(">");
				else if (input[i] == '<')
					lex_error("<");
				else if (input[i] == '>' && input[i] == '>')
					lex_error(">>");
				else
					lex_error("|");
				return (0);
			}
		}
	}
	return (1);
}

int	lex_error_check(char *input)//error_msg
{
	if (!check_spaces(input))
		return (0);
	else if (!check_unclosed_quotes(input))
		return (0);
	else if (!check_pipe(input))
		return (0);
	else if (!check_redir(input))
		return (0);
	return (1);
}
