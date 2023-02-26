/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:41:01 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/24 23:37:50 by jkroger          ###   ########.fr       */
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
	char	*tmp;

	limiter = token->token;
	input = readline("> ");
	while (input && exit_status != 130)
	{
		if (ft_strcmp(input, limiter) == 0)
			break ;
		if (is_dollar(input))
		{
			tmp = input;
			input = get_var(tmp, env);
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
			free(tmp);
		}
		else
		{
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
		}
		free(input);
		input = readline("> ");
	}
	free(input);
}