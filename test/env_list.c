/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:26:07 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/10 19:04:02 by jkroger          ###   ########.fr       */
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

	env = malloc(count_env_len(envp) + 1 * sizeof(char *));
	if (!env)
		return(NULL);
	i = -1;
	while (envp[++i])
		env[i] = envp[i];
	env[i] = NULL;
	return (env);
}

void	del_env(t_cmds *cmd_lst, char *var)
{
	int i;
	int j;

	i = -1;
	while (cmd_lst->env[++i])
	{
		if (cmd_lst->env[i] == var)//strcmp count strlen till '='
		{
			j = i + 1;
			while (cmd_lst->env[j])
				cmd_lst->env[i++] = cmd_lst->env[j++];
			cmd_lst->env[j++] = NULL;
			free(cmd_lst->env[j]);
		}
	}
}

void	add_env(t_cmds *cmd_lst, char *var)
{
	int		i;
	char	**tmp;

	tmp = cmd_lst->env;
	free(cmd_lst->env);
	cmd_lst->env = malloc(count_env_len(tmp) + 1 * sizeof(char *));
	i = -1;
	while (tmp[++i])
		cmd_lst->env[i] = tmp[i];
	cmd_lst->env[i++] = var;
	cmd_lst->env = NULL;
}
