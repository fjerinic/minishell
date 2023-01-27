/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:01:04 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/27 20:51:49 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*expander(t_tokens **token, char **envp)
{
	//t_tokens	*token_lst;
	int		i;
	int		j;
	char	*tmp;

	while (token != NULL)
	{
		i = -1;
		while ((*token)->token[++i] && (*token)->token[0] != '\'' && (*token)->type == WORD)
		{
			if ((*token)->token[i] == '$' && (*token)->token[i + 1] == ' ' && (*token)->token[i + 1] == '\0')
			{
				tmp = get_var((*token)->token, envp);
				free((*token)->token);
				(*token)->token = tmp;
			}
		}
		//free(tokens);
	}
}