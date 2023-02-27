/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:16:41 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/27 20:02:19 by jkroger          ###   ########.fr       */
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

char	*ft_find_path(char **env, char *cmd)
{
	t_path	p;
	char	*envp;

	envp = path_finder(env);
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
