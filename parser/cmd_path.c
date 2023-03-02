/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:16:41 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/02 15:24:15 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_path
{
	char	**path_hold;
	char	*cmd_path;
	int		i;
}t_path;

int	cmd_or_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (1);
	else
		return (0);
}

void	free_path_holder(char **path_holder)
{
	int	i;

	i = 0;
	while (path_holder[i])
		free(path_holder[i++]);
	free(path_holder);
}

char	*path_finder(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (ft_substr(env[i], 5, ft_strlen(env[i]) - 5));
		i++;
	}
	return (NULL);
}

int	check_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	else if (ft_strcmp(cmd, "env") == 0)
		return (0);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (0);
	return (1);
}

char	*ft_find_path(char **env, char *cmd, int *err)
{
	t_path	p;
	char	*envp;

	envp = path_finder(env);
	
	if (envp == NULL && check_builtin(cmd) != 0)
	{
		write(2, "shell: ", 7);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": No such file or directory\n", 28);
		*err = -1;
		return (NULL);
	}

	if (cmd_or_path(cmd))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		else
			return(NULL);
	}
	else
	{
		p.path_hold = ft_split(envp, ':');
		free(envp);//??
		p.i = -1;
		while (p.path_hold[++p.i])
		{
			p.cmd_path = edited_strjoin(ft_strjoin(p.path_hold[p.i], "/"), cmd);
			if (access(p.cmd_path, F_OK | X_OK) == 0)
			{
				free_path_holder(p.path_hold);
				return (p.cmd_path);
			}
			free(p.cmd_path);
		}
	}
	free_path_holder(p.path_hold);
	return (NULL);
}
