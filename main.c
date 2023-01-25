/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:38:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/24 19:55:22 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <readline/readline.h>
#include <stdio.h>

int	minishell(void)
{
	char *input;

	input = user_input();

	//handle_signals()
	if (parser(input))
		error_msg();
	//expander()	

	//execution()
	return (0);
}



int main(void)
{
	int status;

	status = 0;
	while (!status)
		status = minishell();
}