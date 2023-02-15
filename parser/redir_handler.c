/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:27:06 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/15 20:24:08 by jkroger          ###   ########.fr       */
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

int	here_doc(t_tokens *token, int infile)
{
	char	*input;
	char	*limiter;
	
	(void)token;
	if (infile != 0)
		close(infile);
	infile = open(".heredoc.tmp", O_APPEND \
		| O_CREAT | O_RDWR, 0000644);//unlink use pipe
	if (infile < 0)
		return (-1);
	limiter = token->token;
	input = readline("> ");
	while (input)
	{
		if (ft_strcmp(input, limiter) == 0)
		{
			free(limiter);
			//free(input);
			break ;
		}
		write(infile, input, ft_strlen(input));
		write(infile, "\n", 1);
		// if (write(infile, input, ft_strlen(input)) == -1)
		// {
		// 	free(input);
		// 	ft_error(pipex, "Error: Could not write to heredoc file!\n");
		// }
		// free(input);
		input = readline("> ");
	}
	char *line = get_next_line(infile);
	printf("line = %s\n", line);
	return (infile);
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

void	redir_handler(t_tokens *token, t_cmds *cmd)
{
	if (token->type == REDIR_INPUT)
		cmd->infile	= input_redir(token, cmd->infile);
	else if (token->type == REDIR_OUTPUT)
		cmd->outfile = output_redir(token, cmd->outfile);
	else if (token->type == HERE_DOC)
		cmd->infile = here_doc(token, cmd->infile);
	else
		cmd->outfile = append(token, cmd->outfile);
}
