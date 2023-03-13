/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:56:19 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/13 14:26:17 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (!vars)
		return (NULL);
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

// char	**add_env(char **env, char *var)
// {
// 	int		i;
// 	char	**envcp;

// 	if (!var)
// 		return (env);
// 	if (ft_var(env, var))
// 		envcp = malloc((count_env_len(env) + 1) * sizeof(char *));
// 	else
// 		envcp = malloc((count_env_len(env) + 2) * sizeof(char *));
// 	if (!envcp)
// 		return (NULL);
// 	i = 0;
// 	while (env && env[i])
// 	{
// 		if (!ft_strncmp(env[i], var, len_equal(var)))
// 			envcp[i] = ft_strdup(var);
// 		else
// 			envcp[i] = ft_strdup(env[i]);
// 		i++;
// 	}
// 	if (!ft_var(env, var))
// 		envcp[i++] = ft_strdup(var);
// 	envcp[i] = NULL;
// 	if (env)
// 	{
// 		i = -1;
// 		while(env[++i])
// 			free(env[i]);
// 		free(env);
// 	}
// 	return (envcp);
// }

// void	builtin_export(t_cmds *cmd)
// {
// 	int i;

// 	if (!cmd->cmd_split[1])
// 		return (cmd->env);
// 	i = 0;
// 	while (cmd->cmd_split[++i])
// 	{
// 		if (!ft_isalpha(cmd->cmd_split[i][0]))
// 		{
// 			// exit_status = 1;
// 			//err msg
// 			continue ;
// 		}
// 		if (ft_strchr(cmd->cmd_split[i], '='))
// 			cmd->env = add_env(cmd->env, cmd->cmd_split[i]);
// 		else
// 			cmd->env = add_env(cmd->env, find_var(cmd->var_lst, cmd->cmd_split[i]));
// 	}
// 	return (cmd->env);
// }



//export has to check if cmd->next == NULL if yes then execute
//as="aas" has also to be added








void	add_env(t_cmds *cmd, char *var)
{
	int		i;
	char	**envcp;

	if (!var)
		return ;
	envcp = cmd->env;
	if (ft_var(envcp, var))
		cmd->env = malloc((count_env_len(envcp) + 1) * sizeof(char *));
	else
		cmd->env = malloc((count_env_len(envcp) + 2) * sizeof(char *));
	if (!cmd->env)
		return ;//assign bacK?
	i = 0;
	while (envcp && envcp[i])
	{
		if (!ft_strncmp(envcp[i], var, len_equal(var)))
			cmd->env[i] = ft_strdup(var);
		else
			cmd->env[i] = ft_strdup(envcp[i]);
		i++;
	}
	if (!ft_var(envcp, var))
		cmd->env[i++] = ft_strdup(var);
	cmd->env[i] = NULL;
	if (envcp)
	{
		i = -1;
		while(envcp[++i])
			free(envcp[i]);
		free(envcp);
	}
}

void	builtin_export(t_cmds *cmd)
{
	int i;

	if (!cmd->cmd_split[1])
		return ;
	i = 0;
	while (cmd->cmd_split[++i])
	{
		if (!ft_isalpha(cmd->cmd_split[i][0]))
		{
			// exit_status = 1;
			//err msg
			continue ;
		}
		if (ft_strchr(cmd->cmd_split[i], '='))
			add_env(cmd, cmd->cmd_split[i]);
		else
			add_env(cmd, find_var(cmd->var_lst, cmd->cmd_split[i]));
	}
}
