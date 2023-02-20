/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:27:06 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/20 20:40:38 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	input_redir(t_tokens *token, int infile)
{
	if (infile != 0)
		close(infile);
	infile = open(token->token, O_RDONLY);
	if (infile < 0)
		return (-1);
	return (infile);
}

int	output_redir(t_tokens *token, int outfile)
{	
	if (outfile != 1)
		close(outfile);
	outfile = open(token->token, O_TRUNC | O_CREAT | O_WRONLY, 0000644);//0777
	if (outfile < 0)
		return (-1);
	return (outfile);
}

void	here_doc(t_tokens *token, int *infile, char **env)
{
	int		fd[2];
	
	if (*infile != 0)
		close(*infile);
	pipe(fd);//err
	here_doc_loop(token, fd[1], env);
	close(fd[1]);
	*infile = fd[0];
	//close(fd[0]);
}

int	append(t_tokens *token, int outfile)
{
	if (outfile != 1)
		close(outfile);
	outfile = open(token->token,O_TRUNC | O_CREAT | O_APPEND, 0000644);//0777
	if (outfile < 0)
		return (-1);
	return (outfile);
}

void	redir_handler(t_tokens *token, t_cmds *cmd, char **env)
{
	if (token->type == REDIR_INPUT)
		cmd->infile	= input_redir(token, cmd->infile);
	else if (token->type == REDIR_OUTPUT)
		cmd->outfile = output_redir(token, cmd->outfile);
	else if (token->type == HERE_DOC)
		here_doc(token, &cmd->infile, env);
	else
		cmd->outfile = append(token, cmd->outfile);
}
