/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:41:01 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/21 20:25:59 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	exit_status;

int	is_dollar(char *input)
{
	int	i;
	
	i = -1;
	while (input[++i])
	{
		if (input[i] == '$')
			return (1);
	}
	return (0);
}

void	here_doc_loop(t_tokens *token, int fd, char **env)
{
	char	*input;
	char	*limiter;

	// here_signal();

	limiter = token->token;
	input = readline("> ");
	while (input && exit_status != 130)
	{
		if (ft_strcmp(input, limiter) == 0)
		{
			free(limiter);
			//free(input);
			break ;
		}
		if (is_dollar(input))
		{
			input = get_var(input, env);
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
			free(input);
		}
		else
		{
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
		}
		// if (write(infile, input, ft_strlen(input)) == -1)
		// {
		// 	free(input);
		// 	ft_error(pipex, "Error: Could not write to heredoc file!\n");
		// }
		// free(input);
		input = readline("> ");
	}
	// if (!input)
	// 	error_msg
}