/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 20:51:29 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/27 20:59:28 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_finder(char **envp, char *var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], edited_strjoin(var, "="), ft_strlen(var) + 1))//free
			return (ft_substr(envp[i], ft_strlen(var) + 1, ft_strlen(envp[i]) - ft_strlen(var) + 1));//get_env()
		i++;
	}
	return (NULL);
}

void	var_exist(char *token, char **envp, int *i, char **var_value)
{
	int		j;
	
	j = *i + 1;
	while ((token[j] >= 'a' && token[j] <= 'z') ||  (token[j] >= 'A' && token[j] <= 'Z')
				|| (token[j] >= '0' && token[j] <= '9'))
		j++;
	*var_value = var_finder(envp, ft_substr(token, *i, j + 1 - *i));//free
	*i = j;
}

char	*get_var(char *token, char **envp) //need actual length of the string to malloc //problme when 2*$ //or when var not existing
{
	int		i;
	int		j;
	int		k;
	int		var_len;
	char	*var_value;
	char	*tmp;
	
	i = -1;
	var_len = 0;
	while (token[++i])
	{
		var_len++;
		if (token[i] == '$' && token[i + 1] != '?' && token[i + 1] != '$')
		{
			var_exist(token, envp, &i, &var_value);//free(var_value)	
			var_len += ft_strlen(var_value);
			free(var_value);
		}
		// else if (token[i] == '$' && token[i + 1] != '?' && token[i + 1] != '$')
		// {
			//get exit status
			//get  pid
		// }		
	}
	var_value = malloc(var_len * sizeof(char));
	i = 0;
	j = 0;
	while (j < var_len--)
	{
		if (token[i] == '$')
		{
			k = 0;
			var_exist(token, envp, &i, &tmp);//free(var_value)
			while (tmp[k])
				var_value[j++] = tmp[k++];
		}
		var_value[j++] = token[i++];
	}
	return (var_value);
}