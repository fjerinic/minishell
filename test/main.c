/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:38:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/10 19:59:35 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmds	*innit_default_cmd(char **envp)
{
	t_cmds *cmd;
	
	cmd = malloc(sizeof(t_cmds));
	if (!cmd)
		return (NULL);

	cmd->env = copy_env(envp);
	cmd->infile = 0;
	cmd->outfile = 1;
	cmd->cmd_split = NULL;
	cmd->cmd_path = NULL;
	return (cmd);
}

int	minishell(char **envp)
{
	char 	*input;
	t_cmds	*cmd_lst = NULL;

	// char **env = copy_env(envp);
	
	
	
	input = user_input();
	
	cmd_lst = innit_default_cmd(envp);
	
	//handle_signals()
	// if (parser(input))
	// 	error_msg();
	parse(input, cmd_lst);//cmd_lst

	//execution()
	return (0);
}

int main(int argc, char *argv[], char **envp)
{
	int status;

	if (argc > 1)
		return (0);
	(void)argv;
	status = 0;
	while (!status)
		status = minishell(envp);
}