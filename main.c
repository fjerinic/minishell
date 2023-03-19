/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:38:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/19 20:25:46 by jkroger          ###   ########.fr       */
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
		free_env(cmd_lst);
		exit(g_exit_status);
	}
	cmd_lst = parse(cmd_lst, input, cmd_lst->env);
	free(input);
	if (cmd_lst->err == -2 || g_exit_status == 130)
	{
		free_cmd_lst(cmd_lst);
		return (0);
	}
	var_lst(cmd_lst);
	run_commands(cmd_lst);
	free_cmd_lst(cmd_lst);
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

void	if_first_check(int *old_fds, t_cmds *cmd_struct,
									int previous_command_exists)
{
	if (previous_command_exists)
	{	
		if (cmd_struct->infile != 0)
		{
			close(old_fds[WRITE_END]);
			dup2(cmd_struct->infile, STDIN_FILENO);
			close(cmd_struct->infile);
			close(old_fds[READ_END]);
		}
		else
		{
			dup2(old_fds[READ_END], STDIN_FILENO);
			close(old_fds[READ_END]);
			close(old_fds[WRITE_END]);
		}
	}
	else
	{
		if (cmd_struct->infile != 0)
		{
			dup2(cmd_struct->infile, STDIN_FILENO);
			close(cmd_struct->infile);
		}
	}
}

int	fork_failed(int pid)
{
	if (pid == -1)
	{
		set_exit_status("Error: Could not fork the process\n", 1);
		return (1);
	}
	return (0);
}

void	run_commands(t_cmds *cmd_lst)
{
	int		pid;
	int		new_fds[2];
	int		old_fds[2];
	int		wait_status;

	pid = 0;
	while (cmd_lst)
	{
		if (cmd_lst->cmd_split && is_builtin(cmd_lst))
		{
			if (!pipe_builtin(cmd_lst, old_fds, new_fds, 1))
				return ;
			cmd_lst = cmd_lst->next;
			continue ;
		}
		else
			if (!pipe_builtin(cmd_lst, old_fds, new_fds, 0))
				return ;
		pid = fork();
		if (fork_failed(pid))
			return ;
		execute_redirect(pid, old_fds, new_fds, cmd_lst);
		cmd_lst = cmd_lst->next;
	}
	wait_for_children(pid, &wait_status);
}
