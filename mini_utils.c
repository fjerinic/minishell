/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:38:59 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/24 17:09:03 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*user_input(void)
{
	char	*prompt;
	char	*input;

	prompt = "minshell$> ";
	input = readline(prompt);//free
	if (ft_strlen(input))
		add_history(input);
	return (input);
}