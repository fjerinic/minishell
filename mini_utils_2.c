/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:26:12 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/16 15:47:53 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_both_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	ptr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ptr)
		return (set_exit_status("Failed to Malloc", 1));
	i = 0;
	if (s1)
	{
		i = -1;
		while (s1[++i])
			ptr[i] = s1[i];
		free(s1);
	}
	j = 0;
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	free(s2);
	return (ptr);
}

int	valid_input(char *input)
{
	int	i;

	i = 0;
	if (!ft_isalpha(input[i]))
		return (0);
	while (input[++i] && input[i] != '=')
	{
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return (0);
	}
	return (1);
}

void	free_env(t_cmds *cmd)
{
	int	i;

	i = 0;
	if (cmd->env)
	{
		while (cmd->env[i])
			free(cmd->env[i++]);
		free(cmd->env);
	}
	i = 0;
	if (cmd->var_lst)
	{
		while (cmd->var_lst[i])
			free(cmd->var_lst[i++]);
		free(cmd->var_lst);
	}
	free(cmd);
}
