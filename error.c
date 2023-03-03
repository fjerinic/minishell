/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:28:35 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/03 16:32:08 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *token, int exit_code)
{
	write(2, "shell: ", 44);
	write(2, token, ft_strlen(token));
	write(2, ": comman not found\n", 19);
	g_exit_status = exit_code;
}

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
	write(2, strerror(err), ft_strlen(strerror(err)));
	write(2, "\n", 1);
	g_exit_status = err;
}
