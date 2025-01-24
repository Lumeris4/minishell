/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:29:18 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:29:18 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	s;
	size_t	i;

	i = 0;
	s = ft_strlen(src);
	if (size == 0)
		return (s);
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (s);
}
/*
#include <stdio.H>
int main() {
    char source[] = "Hello, World !";
    char destination[10]; 

    ft_strlcpy(destination, source, 10);

    printf("Nouvelle chaine: %s\n", destination);

    return 0;
}
*/