/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:08:45 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/17 17:28:16 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse(char *input, char **envp)
{
	t_tokens	*token_lst = NULL;
	t_cmds		*cmd_lst = NULL;

	if(!lex_error_check(input))
		return (0);
	token_lst = lexer(token_lst, input);
	token_lst = expander(token_lst, envp);
	if (innit_cmd_struct(&token_lst, &cmd_lst, envp) != 1)
		return (0);
	return (1);
}

// int k;
// while (cmd_lst != NULL)
// {
// 	k = -1;
// 	printf("path = %s\n", cmd_lst->cmd_path);
// 	if (cmd_lst->cmd_split)
// 	{
// 		while (cmd_lst->cmd_split[++k])
// 			printf("cmd_split = %s\n", cmd_lst->cmd_split[k]);
// 	}
// 	printf("infile = %i\n", cmd_lst->infile);
// 	printf("outfile = %i\n", cmd_lst->outfile);
// 	cmd_lst = cmd_lst->next;
// }
// int j = -1;
// while (envp[++j])
// 	printf("env = %s\n", envp[j]);
// printf("env = %s\n", envp[j]);
// char *line = get_next_line(cmd_lst->infile);
// while (line)
// {
// 	printf("line = %s\n", line);
// 	line = get_next_line(cmd_lst->infile);
// }