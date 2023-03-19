/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:29:52 by fjerinic          #+#    #+#             */
/*   Updated: 2023/03/19 19:55:12 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_child(int *old_fds, int *new_fds,
			t_cmds *cmd_struct, int previous_command_exists)//changes here*********
{
	if_first_check(old_fds, cmd_struct, previous_command_exists);
	if (cmd_struct->next)
	{
		if (cmd_struct->outfile != 1)
		{
			close(new_fds[READ_END]);
			dup2(cmd_struct->outfile, STDOUT_FILENO);
			close(cmd_struct->outfile);
			close(new_fds[WRITE_END]);
		}
		else
		{
			close(new_fds[READ_END]);
			dup2(new_fds[WRITE_END], STDOUT_FILENO);
			close(new_fds[WRITE_END]);
		}
		
	}
	else
	{
		if (cmd_struct->outfile != 1)
		{
			dup2(cmd_struct->outfile, STDOUT_FILENO);
			close(cmd_struct->outfile);
		}
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
	if (cmd_struct->next)
	{
		old_fds[0] = new_fds[0];
		old_fds[1] = new_fds[1];
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
			set_exit_status("Error: command not found\n", 127);
			exit(127);
		}
		else
		{
			execve(cmd_lst->cmd_path,
				cmd_lst->cmd_split, cmd_lst->env);
			set_exit_status("Error: command not found\n", 127);
		}
	}
}

void	wait_for_children(int pid, int *waitpid_status)
{
	while (pid > 0) 
		pid = wait(waitpid_status);
	if (WIFEXITED(*waitpid_status))
		g_exit_status = WEXITSTATUS(*waitpid_status);
}


int	pipe_builtin(t_cmds *cmd_lst, int *old_fds, int *new_fds, int flag)
{
	if (cmd_lst->next)
	{
		if (pipe(new_fds))
		{
			set_exit_status("Error: Could not create pipe\n", 1);
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