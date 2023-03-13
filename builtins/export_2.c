/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 23:03:13 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/13 14:18:46 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// void	add_var(t_cmds *cmd, char *var)
// {
// 	int		i;
// 	char	**varcp;

// 	cmd->var_lst = varcp;
// 	if (!var)
// 		return ;
// 	if (ft_var(varcp, var))
// 		cmd->var_lst = malloc((count_env_len(varcp) + 1) * sizeof(char *));
// 	else
// 		cmd->var_lst = malloc((count_env_len(varcp) + 2) * sizeof(char *));
// 	if (!cmd->var_lst)
// 		return (NULL);
// 	i = 0;
// 	while (varcp && varcp[i])
// 	{
// 		if (!ft_strncmp(varcp[i], var, len_equal(var)))
// 			cmd->var_lst[i] = ft_strdup(var);
// 		else
// 			cmd->var_lst[i] = ft_strdup(varcp[i]);
// 		i++;
// 	}
// 	if (!ft_var(varcp, var))
// 		cmd->var_lst[i++] = ft_strdup(var);
// 	cmd->var_lst[i] = NULL;
// 	if (varcp)
// 	{
// 		i = -1;
// 		while(varcp[++i])
// 			free(varcp[i]);
// 		free(varcp);
// 	}
// }


// void	var_lst(t_cmds *cmd)
// {
// 	int i;
	
// 	if (!cmd->cmd_split)
// 		return (cmd->var_lst);
// 	if (cmd->prev == 0 && cmd->next == NULL && ft_strchr(cmd->cmd_split[0], '=') && ft_isalpha(cmd->cmd_split[0][0]))
// 	{
// 		i = -1; 
// 		while (cmd->cmd_split[++i])
// 			cmd->var_lst = add_env(cmd->var_lst, cmd->cmd_split[i]);
// 	}
// 	return (cmd->var_lst);
// }