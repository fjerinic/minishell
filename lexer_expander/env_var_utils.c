/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 20:51:29 by jkroger           #+#    #+#             */
/*   Updated: 2023/02/27 14:22:08 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*var_finder(char **envp, char *var)
{
	int	i;
	int	j;

	i = 0;
	var = edited_strjoin(var, "=");
	while (envp[i])
	{
		if (ft_strnstr(envp[i], var, ft_strlen(var)))
		{
			j = ft_strlen(var);
			free(var);
			return (ft_substr(envp[i], j, ft_strlen(envp[i]) - j + 1));
		}
		i++;
	}
	free(var);
	return (NULL);
}

void	var_exist(char *token, char **envp, int *i, char **var_value)
{
	int		j;
	
	j = *i + 1;
	while ((token[j] >= 'a' && token[j] <= 'z') ||  (token[j] >= 'A' && token[j] <= 'Z')
				|| (token[j] >= '0' && token[j] <= '9'))
		j++;
	if ((j - *i) == 1)
	{
		while (token[j] && token[j + 1] != '$')
			j++;
		*var_value = ft_substr(token, *i, j - *i);
	}
	else
		*var_value = var_finder(envp, ft_substr(token, *i + 1, j - *i - 1));
	*i = j;
}

int	get_len(char *token, char **envp)
{
	int		i;
	int		var_len;
	char	*var_value;
	
	i = -1;
	var_len = 0;
	while (token[++i])
	{
		if(token[i] != '$')
			var_len++;
		if (token[i] == '$' && token[i + 1] != '?' && token[i + 1] != '$')//maybe not needed token[i + 1] != '$'
		{
			var_exist(token, envp, &i, &var_value);
			var_len += ft_strlen(var_value);
			free(var_value);
			i--;
		}
		else if (token[i] == '$' && token[i + 1] == '?')
		{
			var_value = ft_itoa(exit_status);
			var_len += ft_strlen(var_value);
			free(var_value);
		}
	}
	return (var_len);
}



char	*get_var(char *token, char **envp)
{
	int		i;
	int		j;
	int		k;
	char	*var_value;
	char	*tmp;

	var_value = malloc(get_len(token, envp) + 1 * sizeof(char));
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] != '?' && token[i + 1] != '$')
		{
			k = 0;
			var_exist(token, envp, &i, &tmp);
			if(tmp)
			{
				while (tmp[k])
					var_value[j++] = tmp[k++];
				free(tmp);
				tmp = NULL;
			}
		}
		else if(token[i] == '$' && token[i + 1] == '?')
		{
			k = 0;
			tmp = ft_itoa(exit_status);
			if(tmp)
			{
				while (tmp[k])
					var_value[j++] = tmp[k++];
				free(tmp);
				tmp = NULL;
			}
			i += 2;
		}
		else
			var_value[j++] = token[i++];
	}
	var_value[j] = '\0';
	return (var_value);
}
