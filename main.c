/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:38:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/10 21:31:22 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	minishell(t_cmds *cmd_lst)
{
	char	*input;

	get_signals();
	input = user_input();
	if (!input)
	{
		printf("exit\n");
		g_exit_status = 130;

		int i;
		i = 0;
		while (cmd_lst->env[i])
			free(cmd_lst->env[i++]);
		free(cmd_lst->env);
		free(cmd_lst);
		
		exit(g_exit_status);
	}
	cmd_lst = parse(cmd_lst, input, cmd_lst->env);
	free(input);
	if (cmd_lst->err == -2)
	{
		reset_cmd_struct(cmd_lst);
		return (0);
	}	
	//envp = unset export cd
	//execution()
	// free_cmd_lst(cmd_lst);
	reset_cmd_struct(cmd_lst);	//after exec
	
	/* if (exit_status != 130)
		free_cmd(cmd_lst); */
	//free cmd_lst and env
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_cmds	*cmd_lst;

	if (argc > 1)
		return (0);
	(void)argv;
	g_exit_status = 0;
	cmd_lst = cmd_struct(envp, 0);
	while (1)
		minishell(cmd_lst);
}
