/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 20:51:29 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/28 21:54:54 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*var_finder(char **envp, char *var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], ft_strjoin(var, "="), ft_strlen(var) + 1))//free //edited_strjoin
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
	if (j == 1)
	{
		while (token[j + 1] != '$')
			j++;
		*var_value = ft_substr(token, *i + 1, j - *i - 1);//free
		*i = j;
	}	
	else
	{
		*var_value = var_finder(envp, ft_substr(token, *i + 1, j - *i - 1));//free
		*i = j;
	}
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
			var_len++;//conflicting
		if (token[i] == '$' && token[i + 1] != '?' && token[i + 1] != '$')//maybe not needed token[i + 1] != '$'
		{
			var_exist(token, envp, &i, &var_value);//free(var_value)	//i 1 too much
			var_len += ft_strlen(var_value);
			free(var_value);
			i--;
		}
		// else if (token[i] == '$' && token[i + 1] != '?' && token[i + 1] != '$')
		// {
			//make note for exec
			//get exit status
			//get  pid
			//token = ft_strdup(exit_value);//if$?
		// }
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
	while (j < get_len(token, envp))
	{
		if (token[i] == '$')
		{
			k = 0;
			var_exist(token, envp, &i, &tmp);//free(var_value)
			while (tmp[k])//maybe here some problems if(tmp)
				var_value[j++] = tmp[k++];
			tmp = NULL;
		}
		else
			var_value[j++] = token[i++];
	}
	var_value[j] = '\0';
	return (var_value);
}