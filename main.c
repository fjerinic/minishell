/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:38:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/08 16:23:14 by jkroger          ###   ########.fr       */
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
		//free(envp)
		printf("exit\n");
		g_exit_status = 130;
		exit(g_exit_status);
	}
	cmd_lst = parse(cmd_lst, input, cmd_lst->env);
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
	t_cmds	*cmd_lst;

	if (argc > 1)
		return (0);
	(void)argv;
	status = 0;
	g_exit_status = 0;
	cmd_lst = cmd_struct(envp, 0);//check for cmd_lst == NULL
	while (!status)
		status = minishell(cmd_lst);
}
