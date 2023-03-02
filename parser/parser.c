/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:08:45 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/02 17:02:13 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmds	*parse(char *input, char **envp)
{
	t_tokens	*token_lst = NULL;
	t_cmds		*cmd_lst = NULL;

	if(!lex_error_check(input))
		return (0);
	token_lst = lexer(token_lst, input);
	token_lst = expander(token_lst, envp);
	exit_status = 0;
	if (innit_cmd_struct(&token_lst, &cmd_lst, envp) != 1)
		return (NULL);
	return (cmd_lst);
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
// 	if (cmd_lst->infile != -1 && cmd_lst->infile != 0)
// 	{
// 		char *line = get_next_line(cmd_lst->infile);
// 		while (line)
// 		{
// 			printf("line = %s\n", line);
// 			line = get_next_line(cmd_lst->infile);
// 		}
// 	}
// 	cmd_lst = cmd_lst->next;
// }
// int j = -1;
// while (envp[++j])
// 	printf("env = %s\n", envp[j]);
// printf("env = %s\n", envp[j]);


//cat abc | < main.c grep ";2C;2Ca " | ls > a.txt < ahdgsa | << a grep -a -av -äv | echo $USER$shd$/sur "$//GDFS $USEDSSD  $USER "