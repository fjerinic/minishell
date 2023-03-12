/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:56:19 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/12 11:43:12 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_equal(char *var)
{
	int	i;

	if (!var)
		return (0);
	i = -1;
	while (var[++i])
	{
		if (var[i] == '=')
			return (i);
	}
	return (0);
}

int	ft_var(char **vars, char	*var)
{
	int	i;

	if (!vars)
		return (0);
	i = 0;
	while (vars[i])
	{
		if (!ft_strncmp(vars[i], var, len_equal(var)))
			return (1);
		i++;
	}
	return (0);
}

char	*find_var(char **vars, char *var)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(var, "=");
	while (vars[i])
	{
		if (ft_strnstr(vars[i], tmp, ft_strlen(tmp)))
		{
			free(tmp);
			return (vars[i]);
		}
		i++;
	}
	free(tmp);
	return (NULL);
}

char	**add_env(char **env, char *var)
{
	int		i;
	char	**envcp;

	if (!var)
		return (env);
	if (ft_var(env, var))
		envcp = malloc((count_env_len(env) + 1) * sizeof(char *));
	else
		envcp = malloc((count_env_len(env) + 2) * sizeof(char *));
	if (!envcp)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], var, len_equal(var)))
			envcp[i] = ft_strdup(var);
		else
			envcp[i] = ft_strdup(env[i]);
		i++;
	}
	if (!ft_var(env, var))
		envcp[i++] = ft_strdup(var);
	envcp[i] = NULL;
	if (env)
	{
		i = -1;
		while(env[++i])
			free(env[i]);
		free(env);
	}
	return (envcp);
}

char	**ft_export(t_cmds *cmd)
{
	int i;

	if (!cmd->cmd_split[1])
		return (cmd->env);
	i = 0;
	while (cmd->cmd_split[++i])
	{
		if (!ft_isalpha(cmd->cmd_split[i][0]))
		{
			//err msg
			continue ;
		}
		if (ft_strchr(cmd->cmd_split[i], '='))
			cmd->env = add_env(cmd->env, cmd->cmd_split[i]);
		else
			cmd->env = add_env(cmd->env, find_var(cmd->var_lst, cmd->cmd_split[i]));
	}
	return (cmd->env);	
}

char	**add_var(t_cmds *cmd)
{
	int i;
	
	if (cmd->prev == 0 && cmd->next == NULL && ft_strchr(cmd->cmd_split[0], '=') && ft_isalpha(cmd->cmd_split[0][0]))
	{
		i = -1; 
		while (cmd->cmd_split[++i])
			cmd->var_lst = add_env(cmd->var_lst, cmd->cmd_split[i]);
	}
	
	return (cmd->var_lst);
}

//export has to check if cmd->next == NULL if yes then execute
//as="aas" has also to be added