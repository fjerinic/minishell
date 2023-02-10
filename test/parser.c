/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:08:45 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/10 19:48:26 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse(char *input, t_cmds *cmd_lst)
{

	
	t_tokens	*token_lst = NULL;
	// t_cmds		*cmd_lst = NULL;

	if(!lex_error_check(input))
		return (0);

	
	token_lst = lexer(token_lst, input);

	//innit_cmd_env
	
	token_lst = expander(token_lst, cmd_lst->env);//env

	
	if (innit_cmd_struct(&token_lst, &cmd_lst, cmd_lst->env) != 1)//env
		return (0);

	int k;
	while (cmd_lst != NULL)
	{
		k = -1;
		printf("path = %s\n", cmd_lst->cmd_path);
		while (cmd_lst->cmd_split[++k])
			printf("cmd_split = %s\n", cmd_lst->cmd_split[k]);
		printf("infile = %i\n", cmd_lst->infile);
		printf("outfile = %i\n", cmd_lst->outfile);
		cmd_lst = cmd_lst->next;
	}
	return (1);
}
