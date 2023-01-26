/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:16:13 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/26 14:35:47 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_len(char *s, int *i)
{
	char    quote;
    int     tmp;

    tmp = *i;
    quote = s[tmp++];
	while (s[tmp] != quote && s[tmp])
        tmp++;    
    *i = tmp;
	return (*i);
}