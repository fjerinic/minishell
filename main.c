/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:38:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/26 15:13:22 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(void)
{
	char *input;

	input = user_input();

	//handle_signals()
	// if (parser(input))
	// 	error_msg();
	parse(input);
	
	//expander()	

	//execution()
	return (1);
}



int main(void)
{
	int status;

	status = 0;
	while (!status)
		status = minishell();
}