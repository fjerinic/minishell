/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:09:46 by jkroger           #+#    #+#             */
/*   Updated: 2022/06/07 16:48:54 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
