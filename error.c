/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:28:35 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/15 20:48:16 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_error(char *token)
{
	write(2, "shell:  syntax error near unexpected token `", 44);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
	g_exit_status = 2;
}

void	set_err(char *token, int err)
{
	write(2, "shell: ", 7);
	write(2, token, ft_strlen(token));
	write(2, ": ", 2);
	if (err == -3)
		write(2, "command not found", 17);
	else
		write(2, strerror(err), ft_strlen(strerror(err)));
	write(2, "\n", 1);
	g_exit_status = 127;
}

void	set_exit_status(char *str, int err)//void*
{
	g_exit_status = err;
	write(2, "shell: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

char	*set_exit_str(char *str, int err)
{
	set_exit_status(str, err);
	return (NULL);
}

t_tokens	*set_exit_tkn(char *str, int err)
{
	set_exit_status(str, err);
	return (NULL);
}

t_cmds	*set_exit_cmd(char *str, int err)
{
	set_exit_status(str, err);
	return (NULL);	
}
