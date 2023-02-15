/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:26:07 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/15 18:13:23 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//copy env into a list
//everytime export new var has to bet added to the list every time unset var has to be deleted from the list

int	count_env_len(char **envp)
{
	int	i;

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
		return(NULL);
	i = -1;
	
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	env[i] = NULL;
	return (env);
}

// void	del_env(char **env, char *var)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	while (env[++i])
// 	{
// 		if (env[i] == var)//strcmp count strlen till '='
// 		{
// 			j = i + 1;
// 			while (env[j])
// 				env[i++] = env[j++];
// 			env[j++] = NULL;
// 			free(env[j]);
// 		}
// 	}
// }

// void	add_env(char **env, char *var)
// {
// 	int		i;
// 	char	**tmp;

// 	tmp = env;
// 	free(env);
// 	env = malloc(count_env_len(tmp) + 1 * sizeof(char *));
// 	i = -1;
// 	while (tmp[++i])
// 		env[i] = tmp[i];
// 	env[i++] = var;
// 	env = NULL;
// }
