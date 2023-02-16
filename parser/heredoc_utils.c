/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:41:01 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/16 16:44:26 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_loop(t_tokens *token, int fd)
{
	char	*input;
	char	*limiter;

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
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		// if (write(infile, input, ft_strlen(input)) == -1)
		// {
		// 	free(input);
		// 	ft_error(pipex, "Error: Could not write to heredoc file!\n");
		// }
		// free(input);
		input = readline("> ");
	}
}
