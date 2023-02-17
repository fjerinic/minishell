/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:38:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/17 17:19:06 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(char **envp)
{
	char *input;

	//get_signals();
	input = user_input();

	//handle_signals()
	// if (parser(input))
	// 	error_msg();
	parse(input, envp);

	//execution()
	return (0);
}

int main(int argc, char *argv[], char **envp)
{
	int 	status;
	char	**env;

	if (argc > 1)
		return (0);
	(void)argv;
	status = 0;
	env = copy_env(envp);//free
	while (!status)
		status = minishell(env);
}