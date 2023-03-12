/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:38:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/12 02:26:14 by jkroger          ###   ########.fr       */
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

	cmd_lst->var_lst = add_var(cmd_lst);
	if (ft_strcmp(cmd_lst->cmd_split[0], "export") == 0)
	{
		cmd_lst->env = ft_export(cmd_lst);
		int z = 0;
		while (cmd_lst->cmd_split[++z])
		{
			if (!ft_strchr(cmd_lst->cmd_split[z], '=') && ft_isalpha(cmd_lst->cmd_split[z][0]))
				cmd_lst->var_lst = del_env(cmd_lst->var_lst, cmd_lst->cmd_split[z]);
		}
	}
	free_cmd_lst(cmd_lst);
	
	
	int k = -1;
	while (cmd_lst->env[++k])
		printf("env = %s\n", cmd_lst->env[k]);
	k = -1;
	while(cmd_lst->var_lst[++k])
		printf("var = %s\n", cmd_lst->var_lst[k]);

	//envp = unset export cd
	//execution()
	// free_cmd_lst(cmd_lst);
	
	//reset_cmd_struct(cmd_lst);	//after exec
	
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
