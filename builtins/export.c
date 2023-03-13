/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:56:19 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/13 21:00:42 by jkroger          ###   ########.fr       */
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

char	**sort_export(char **expo)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (expo[++i])
	{
		j = -1;
		while (expo[++j])
		{
			if (ft_strncmp(expo[j], expo[j + 1], ft_strlen(expo[j])) > 0)
			{
				tmp = expo[j];
				expo[j] = expo[j + 1];
				expo[j + 1] = tmp;
			}
		}
	}
	return (expo);
}

char	**put_quotes(char **expo)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = -1;
	while (expo[++i])
	{
		tmp = malloc((ft_strlen(expo[i]) + 3) * sizeof(char));
		if (!tmp)
			return (NULL);
		j = -1;
		k = 0;
		while (expo[i][++j] != '=')
			tmp[k++] = expo[i][j];
		tmp[k++] = expo[i][j];
		tmp[k++] = '"';
		while (expo[i][++j])
			tmp[k++] = expo[i][j];
		tmp[k] = '"';
		tmp[++k] = '\0';
		free(expo[i]);
		expo[i] = tmp;
	}
	return (expo);
}

void	export_without_args(t_cmds *cmd)
{
	char	**expo;
	int		i;

	expo = copy_env(cmd->env);
	expo = sort_export(expo);
	expo = put_quotes(expo);
	i = -1;
	while (expo[++i])
		printf("declare -x %s\n", expo[i]);
	i = -1;
	while (expo[++i])
		free(expo[i]);
	free(expo);
}

void	builtin_export(t_cmds *cmd)
{
	int i;

	if (!cmd->cmd_split[1])
		export_without_args(cmd);
	i = 0;
	while (cmd->cmd_split[++i])
	{
		if (!ft_isalpha(cmd->cmd_split[i][0]) && cmd->cmd_split[i][0] != '_')
		{
			// exit_status = 1;
			//err msg
			continue ;
		}
		if (ft_strchr(cmd->cmd_split[i], '='))
			add_env(cmd, cmd->cmd_split[i]);
		else
		{
			if (find_var(cmd->var_lst, cmd->cmd_split[i]))
			{
				add_env(cmd, find_var(cmd->var_lst, cmd->cmd_split[i]));
				del_var(cmd, cmd->cmd_split[i]);
			}
			// else
			// 	//add_to_export
		}
	}
}
