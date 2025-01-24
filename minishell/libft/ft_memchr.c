/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:28:07 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:28:07 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t n)
{
	size_t					i;
	const unsigned char		*str;
	unsigned char			c;

	str = (const unsigned char *)ptr;
	c = (unsigned char)value;
	i = 0;
	while (i < n)
	{
		if (str[i] == c)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>

int main() {
    char bloc[] = { 'a', 'b', 'c', 'd', 'e' };
    char *resultat = ft_memchr(bloc, 'c', 5);

    if (resultat != NULL) {
        printf("Caractère trouvé : %c\n", *resultat);
    } else {
        printf("Caractère non trouvé.\n");
    }

    return 0;
}
*/