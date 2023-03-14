/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:16:41 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/14 18:15:05 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ft_find_path_2(char *envp, char *cmd)
{
	int		i;
	char	*cmd_path;
	char	**path_hold;

	path_hold = ft_split(envp, ':');
	free(envp);
	i = -1;
	while (path_hold[++i])
	{
		cmd_path = edited_strjoin(ft_strjoin(path_hold[i], "/"), cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free_path_holder(path_hold);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_path_holder(path_hold);
	return (NULL);
}

char	*ft_find_path(char **env, char *cmd, int *err)
{
	char	*envp;

	if (!cmd)
		return (NULL);
	envp = path_finder(env);
	if (!envp)
	{
		if (check_builtin(cmd) != 0 && *err == 0)
			*err = -1;//also errfile
		return (NULL);
	}
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		else
		{
			*err = -1;//also err_file
			return (NULL);
		}
	}
	return (ft_find_path_2(envp, cmd));
}
