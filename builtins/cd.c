/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:24:23 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/07 18:50:03 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//This code implements a cd built-in shell command.
//  The ft_cd function changes the current working 
//  directory to a given absolute or relative path. 
//  If no argument is given, it takes the value of 
//  the $HOME environment variable as the default argument. 
//  The update_env function updates the environment variables 
//  PWD and OLDPWD to reflect the change in the current working 
//  directory. get_env function searches for an environment 
//  variable and returns an allocated string if it exists. 
//  find_pwd_index function finds the index of the 
//  PWD environment variable in an array of environment variables.

void	ft_cd(t_cmd_struct *cmd_struct)
{
	char	*old_path;
	char	*new_path;

	old_path = getcwd(NULL, 0);
	if (cd_home(cmd_struct, old_path))
		return ;
	if (chdir(cmd_struct->split_command[1]))
	{
		if (cmd_struct->split_command[1][0] == '-')
			set_exit_status("Error\n", 1);
		else
			set_exit_status("No such file or directory\n", 1);
		free(old_path);
		return ;
	}
	new_path = getcwd(NULL, 0);
	update_env(cmd_struct, new_path, old_path);
	free(old_path);
	free(new_path);
}


int	cd_home(t_cmd_struct *cmd_struct, char *old_path)
{
	char	*env_return;

	env_return = get_env(cmd_struct, "HOME=");
	if (!env_return)
		return (1);
	if (!cmd_struct->split_command[1])
	{
		if (env_return && chdir(env_return))
		{
			set_exit_status("Error\n", 1);
			free(old_path);
			free(env_return);
			return (1);
		}
		free(old_path);
		free(env_return);
		return (1);
	}
	return (0);
}

// Updates the environment variables PWD and OLDPWD

static void	update_env(t_cmd_struct *cmd_struct, char *new_pwd_path,
				char *old_pwd_path)
{
	int	i;

	i = find_pwd_index(cmd_struct);
	if (cmd_struct->env_clone[i] && ft_strnstr(cmd_struct->env_clone[i],
			"PWD=", 4))
	{
		free(cmd_struct->env_clone[i]);
		cmd_struct->env_clone[i] = ft_strjoin("PWD=", new_pwd_path);
	}
	else
		old_pwd_path = NULL;
	i = 0;
	while (cmd_struct->env_clone[i] && !ft_strnstr(cmd_struct->env_clone[i],
			"OLDPWD", 6))
		i++;
	if (cmd_struct->env_clone[i] && ft_strnstr(cmd_struct->env_clone[i],
			"OLDPWD", 6))
	{
		free(cmd_struct->env_clone[i]);
		cmd_struct->env_clone[i] = ft_strjoin_zero_allowed("OLDPWD=",
				old_pwd_path);
	}
}


int	find_pwd_index(t_cmd_struct *cmd_struct)
{
	int	i;

	i = 0;
	while (cmd_struct->env_clone[i]
		&& !ft_strnstr(cmd_struct->env_clone[i], "PWD=", 4))
	{
		i++;
		if (cmd_struct->env_clone[i] && ft_strnstr(cmd_struct->env_clone[i],
				"OLDPWD=", 7))
			i++;
	}
	return (i);
}

/*
Searches for a environment variable and returns
an allocated string, if it exists.
*/
char	*get_env(t_cmd_struct *cmd_struct, char *str)
{
	char	*env_return;
	int		i;

	i = 0;
	env_return = NULL;
	while (str && cmd_struct->env_clone[i] && !ft_strnstr(
			cmd_struct->env_clone[i], str, ft_strlen(str)))
		i++;
	if (cmd_struct->env_clone[i] && ft_strnstr(cmd_struct->env_clone[i], str,
			ft_strlen(str)))
		env_return = ft_substr(cmd_struct->env_clone[i], 5,
				ft_strlen(cmd_struct->env_clone[i]) - 5);
	else
	{	
		set_exit_status("Error: Environment variable $HOME not found\n", 1);
		env_return = NULL;
	}
	return (env_return);
}