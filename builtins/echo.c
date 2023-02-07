/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:28:37 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/07 17:28:38 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
        return 1;
    }
    int i=1;
    while(i<argc){
        printf("%s",argv[i]);
        if(i < argc-1)
            printf(" ");
        i++;
    }
    printf("\n");
    return 0;
}