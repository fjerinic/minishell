/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:26:07 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/10 13:48:10 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_env_len(char **envp)
{
	int	i;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**copy_env(char **envp)
{
	int		i;
	char	**env;

	env = malloc((count_env_len(envp) + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = -1;
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	env[i] = NULL;
	return (env);
}

int	var_exists(char **env, char *var)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0
			&& env[i][ft_strlen(var)] == '=')
			return (1);
	}
	return (0);
}

char	**del_env(char **env, char *var)
{
	int		i;
	int		j;
	char	**envcp;

	if (var_exists(env, var) == 0)
		return (env);
	envcp = malloc(count_env_len(env) * sizeof(char *));
	i = 0;
	j = 0;
	while (env[j])
	{
		if (ft_strncmp(env[j], var, ft_strlen(var)) == 0)//also with '=' to check for exact
			free(env[j++]);
		else
		{
			envcp[i++] = ft_strdup(env[j]);
			free(env[j++]);
		}
	}
	envcp[i] = NULL;
	free(env);
	return (envcp);
}

char	**add_env(char **env, char *var)
{
	int		i;
	char	**envcp;

	//var_exist replace it
	envcp = malloc((count_env_len(env) + 2) * sizeof(char *));
	i = -1;
	while (env[++i])
	{
		envcp[i] = ft_strdup(env[i]);
		free(env[i]);
	}
	envcp[i++] = ft_strdup(var);
	envcp[i] = NULL;
	free(env);
	return (envcp);
}
