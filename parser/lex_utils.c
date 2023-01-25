/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:16:13 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/25 10:33:36 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	quote_len(char *s, int *i)
{
	char quote;

	quote = s[*i++];
	while (s[*i] != quote)
		*i++;
	return (i);
}