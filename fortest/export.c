#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

	ptr = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*c;
	unsigned char	*d;

	c = (unsigned char *)s1;
	d = (unsigned char *)s2;
	i = 0;

	while (i < n && (s1[i] || s2[i]))
	{
		if (c[i] == d[i])
			i++;
		else
			return (c[i] - d[i]);
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;

	i = 0;
	if (ft_strlen(needle) == ft_strlen(""))
		return ((char *)haystack);
	while (i < ft_strlen(haystack))
	{
		if (i == len)
			return (NULL);
		if (ft_strncmp(&haystack[i], needle, ft_strlen(needle)) == 0)
		{
			if (i + ft_strlen(needle) - 1 >= len)
				return (NULL);
			else
				return ((char *)(&haystack[i]));
		}
		i++;
	}
	return (NULL);
}



char	*edited_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	ptr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			ptr[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (s2[j])
	{
		ptr[i++] = s2[j++];
	}
	ptr[i] = '\0';
	//free(s1);
	return (ptr);
}


/* libft end */

//has to be uptade everytime

int	count_env_len(char **envp)
{
	int	i;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
		i++;
	return (i);
}

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

int	var_exist(char **vars, char	*var)
{
	int	i;

	if (!vars)
		return (0);
	i = 0;
	while (vars[i])
	{
		if (!ft_strncmp(vars[i], var, len_equal(var)))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*var_finder(char **vars, char *var)
{
	int	i;

	i = 0;
	var = edited_strjoin(var, "=");
	while (vars[i])
	{
		if (ft_strnstr(vars[i], var, ft_strlen(var)))
		{
			free(var);
			return (vars[i]);
		}
		i++;
	}
	free(var);
	return (NULL);
}

char	**add_env(char **env, char *var)
{
	int		i;
	char	**envcp;

	if (!var)
		return (env);
	if (var_exist(env, var))
		envcp = malloc((count_env_len(env) + 1) * sizeof(char *));
	else
		envcp = malloc((count_env_len(env) + 2) * sizeof(char *));
	if (!envcp)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var, len_equal(var) - 1))
			envcp[i] = ft_strdup(var);
		else
			envcp[i] = ft_strdup(env[i]);
		//free(env[i]);
	}
	if (!var_exist(env, var))//problem here with free free env at the  end
	{
		envcp[i++] = ft_strdup(var);//has to be checked if var_exist or not
	}
	envcp[i] = NULL;
	// free(env);
	return (envcp);
}

//if var used in export free it from vars list
//check also if cmd->cmd_split has '=' in it

int	with_value(char *s)//strchr
{
	int i;

	i = -1;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
	}
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

char	*ft_strchr(const char	*str, int c)
{
	int	i;

	if (!str || !c)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

void	ft_export(t_cmds *cmd)
{
	int i;

	if (!cmd->cmd_split[1])
		return ;
	i = 0;
	while (cmd->cmd_split[++i])
	{
		if (!ft_isalpha())
		{
			//err msg
			continue ;
		}
		if (ft_strchr(cmd_split[i], '='))
			add_env(cmd->env, cmd_split[i]);
		else
			add_env(envp, var_finder(cmd->vars, cmd_split[i]));
	}
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	char *vars[5] = {"PATH=123", "CD=35564", "EF=234524", "GH=21421343", NULL};

	envp = add_env(envp, var_finder(vars, "asdas"));

	int i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}

//only if command not found not added to cmd->vars

if (cmd_split && cmd->prev == 0 && cmd->next == NULL)
{
	int i;

	//cmd_split has to be modified if EQUAL in it before it gets to execution 
	while ()//ft_strchr(cmd->cmd_split[i], '=') && ft_isalpha(cmd->cmd_split[0][0])

	add_env(cmd->vars);
}
//check for how to args to cmd->vars
//new type for =
//how is it with unset PATH then RIEIR=dafnd cat