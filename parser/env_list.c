/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:26:07 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/13 18:48:12 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_env_len(char **envp)//check here for env builtin
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
