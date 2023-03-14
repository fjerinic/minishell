/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:12:06 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/14 17:15:35 by jkroger          ###   ########.fr       */
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
