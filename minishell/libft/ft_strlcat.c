/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:29:14 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:29:14 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d;
	size_t	i;
	size_t	s;

	i = 0;
	d = ft_strlen(dest);
	s = ft_strlen(src);
	if (size == 0)
		return (s);
	if (size <= d)
		return (s + size);
	while (src[i] && (i + d) < (size - 1))
	{
		dest[i + d] = src[i];
		i++;
	}
	dest[d + i] = '\0';
	return (d + s);
}

/*
#include <stdio.h>
int main() {
	char source[] = "tout le monde";
	char destination[] = "bonjour "; 

	ft_strlcat(destination, source, 4);

	printf("Nouvelle chaine: %s\n", destination);

	return 0;
}
*/
