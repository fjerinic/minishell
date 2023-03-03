/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:38:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/03 18:54:14 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	minishell(char **envp)
{
	char 	*input;
	t_cmds	*cmd_lst;

	cmd_lst = NULL;
	get_signals();
	input = user_input();
	if (!input)
	{
		//free(envp)
		printf("exit\n");
		g_exit_status = 130;

		/* int z = -1;
		while (envp[++z])
			free(envp[z]);
		free(envp); */
		
		exit(g_exit_status);
	}
	cmd_lst = parse(input, envp);
	free(input);
	

	//envp = unset export cd
	
	//execution()
	/* if (exit_status != 130)
		free_cmd(cmd_lst); */
	//free cmd_lst and env
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	int		status;
	char	**env;

	if (argc > 1)
		return (0);
	(void)argv;
	status = 0;
	env = copy_env(envp);
	g_exit_status = 0;
	while (!status)
		status = minishell(env);
}
