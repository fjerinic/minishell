/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:38:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/13 01:09:11 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	minishell(t_cmds *cmd_lst)
{
	char	*input;

	//get_signals();
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
	run_commands(cmd_lst);

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

static void	if_first_check(int *old_fds, t_cmds *cmd_struct,
									int previous_command_exists)
{
	if (previous_command_exists)
	{	
		dup2(old_fds[READ_END], STDIN_FILENO);
		close(old_fds[READ_END]);
		close(old_fds[WRITE_END]);
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

void	run_commands(t_cmds *cmd_lst)
{
	int		pid;
	int		new_fds[2];
	int		old_fds[2];
	int		wait_status;

	pid = 0;
	while (cmd_lst)
	{
		if (is_builtin(cmd_lst))
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
		// if (fork_failed(pid))
		// 	return ;
		execute_redirect(pid, old_fds, new_fds, cmd_lst);
		cmd_lst = cmd_lst->next;
	}
	wait_for_children(pid, &wait_status);
}

int	pipe_builtin(t_cmds *cmd_lst, int *old_fds, int *new_fds, int flag)
{
	if (cmd_lst->next)
	{
		if (pipe(new_fds))
		{
			//set_exit_status("Error: Could not create pipe\n", 1);
			return (0);
		}
		if (flag)
			redirect_parent(old_fds, new_fds, cmd_lst);
	}
	return (1);
}

void	execute_redirect(int pid, int *old_fds, int *new_fds,
			t_cmds *cmd_lst)
{
	execute_child(pid, old_fds, new_fds, cmd_lst);
	redirect_parent(old_fds, new_fds, cmd_lst);
}

void	wait_for_children(int pid, int *waitpid_status)
{
	while (pid > 0) 
		pid = wait(waitpid_status);
	if (WIFEXITED(*waitpid_status))
		g_exit_status = WEXITSTATUS(*waitpid_status);
}

void	execute_child(int pid, int *old_fds, int *new_fds,
			t_cmds *cmd_lst)
{
	if (pid == 0)
	{
		//signal_child_active();
		redirect_child(old_fds, new_fds, cmd_lst,
			cmd_lst->prev); //replaced prev with cmd_lst->prev
		if (is_builtin2(cmd_lst))
			exit(g_exit_status);
		if (access(cmd_lst->cmd_path, X_OK) != 0)
		{
			//set_exit_status("Error: command not found\n", 127);
			exit(127);
		}
		else
		{
			execve(cmd_lst->cmd_path,
				cmd_lst->cmd_split, cmd_lst->env);
			//set_exit_status("Error: command not found\n", 127);
		}
	}
}

void	redirect_child(int *old_fds, int *new_fds,
			t_cmds *cmd_struct, int previous_command_exists)
{
	if_first_check(old_fds, cmd_struct, previous_command_exists);
	if (cmd_struct->next)
	{
		close(new_fds[READ_END]);
		dup2(new_fds[WRITE_END], STDOUT_FILENO);
		close(new_fds[WRITE_END]);
	}
	else
	{
		close(new_fds[READ_END]);
		if (cmd_struct->outfile != 1)
		{
			dup2(cmd_struct->outfile, STDOUT_FILENO);
			close(cmd_struct->outfile);
		}
		close(new_fds[WRITE_END]);
	}
}

void	redirect_parent(int *old_fds, int *new_fds,
			t_cmds *cmd_struct)
{
	if (cmd_struct->prev)
	{
		close(old_fds[1]);
		close(old_fds[0]);
	}
	else
	{
		if (cmd_struct->infile != 0)
			close(cmd_struct->infile);
	}
	if (cmd_struct->next)
	{
		old_fds[0] = new_fds[0];
		old_fds[1] = new_fds[1];
	}
}

int	is_builtin(t_cmds *cmd_lst)
{
	//signal_not_interactive();
	if (!ft_strncmp(cmd_lst->cmd_split[0], "cd", 3))
	{	
		if (cmd_lst->next)
			return (1);
		cd(cmd_lst);
		return (1);
	}
	else if (!ft_strncmp(cmd_lst->cmd_split[0], "export", 7))
	{
		if (cmd_lst->next)
			return (1);
		//builtin_export(cmd_lst);
		//return (1);
	}
	else if (!ft_strncmp(cmd_lst->cmd_split[0], "unset", 6))
	{
		if (cmd_lst->next)
			return (1);
		unset(cmd_lst);
		return (1);
	}
	else if (!ft_strncmp(cmd_lst->cmd_split[0], "exit", 5))
	{
		if (cmd_lst->next)
			return (1);
		builtin_exit(cmd_lst);
		return (1);
	}
	return (0);
}

int	is_builtin2(t_cmds *cmd_lst)
{
	if (!ft_strncmp(cmd_lst->cmd_split[0], "echo", 5))
	{
		echo(cmd_lst);
		return (1);
	}
	else if (!ft_strncmp(cmd_lst->cmd_split[0], "pwd", 4))
	{
		if (cmd_lst->cmd_split[1]
			&& cmd_lst->cmd_split[1][0] == '-')
		{
			//set_exit_status("pwd error\n", 1);
			return (1);
		}
		pwd();
		return (1);
	}
	else if (!ft_strncmp(cmd_lst->cmd_split[0], "env", 4))
	{
		try_env(cmd_lst);
		return (1);
	}
	return (0);
}

void	try_env(t_cmds *cmd_lst)
{
	if (count_env_len(cmd_lst->cmd_split) > 1)
	{
		//set_exit_status("Error: env\n", 1);
		return ;
	}
	env(cmd_lst);
	return ;
}

