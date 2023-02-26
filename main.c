/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:38:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/24 23:31:40 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status;

int	minishell(char **envp)
{
	char 	*input;
	t_cmds	*cmd_lst = NULL;

	get_signals();
	input = user_input();
	if (!input)
	{
		//free(envp)
		printf("exit\n");
		exit_status = 130;

		/* int z = -1;
		while (envp[++z])
			free(envp[z]);
		free(envp); */
		
		exit(exit_status);
	}
	cmd_lst	= parse(input, envp);//error_msg();
	free(input);

	//execution()
	/* if (exit_status != 130)
		free_cmd(cmd_lst); */
	//free cmd_lst and env
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
	env = copy_env(envp);
	exit_status = 0;
	while (!status)
		status = minishell(env);
}

//if general error exit_status = 1;
//if builtin missused exit_status = 2;
//if script with no exec permission exit_status = 126;
//if command doesnt exist exit_status = 128;
//if program terminated by a fatal signal like seg. fault exit_status = 129;
//if program terminated by ctrl + c exit_status = 130;
// if Exit status out of range (e.g. specifying an invalid exit status code in a script or command) exit_status = 255;