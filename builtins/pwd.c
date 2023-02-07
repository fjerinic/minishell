/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:11:33 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/07 17:15:03 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

// Maybe error handling is needed
int ft_pwd(void)
{
    char buffer[1024];
    char *path = getcwd(buffer, sizeof(buffer));
    printf("%s\n", path);
    return 0;
}

