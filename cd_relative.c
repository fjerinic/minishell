/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_relative.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:44:11 by fjerinic          #+#    #+#             */
/*   Updated: 2023/01/28 01:44:36 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }
    char current_path[1024];
    char new_path[1024];
    if (getcwd(current_path, sizeof(current_path)) == NULL) {
        perror("getcwd");
        return 1;
    }
    //argv[1] is the relative path of the directory to change to
    snprintf(new_path, sizeof(new_path), "%s/%s", current_path, argv[1]);
    if (chdir(new_path) == -1) {
        perror("chdir");
        return 1;
    }
    return 0;
}