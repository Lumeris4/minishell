/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:28:12 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:28:12 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t n)
{
	size_t				i;
	const unsigned char	*s1;
	const unsigned char	*s2;

	i = 0;
	s1 = (const unsigned char *)ptr1;
	s2 = (const unsigned char *)ptr2;
	while (i < n)
	{
		if (s1[i] > s2[i])
			return (1);
		if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int main() {
	char bloc1[] = { 'a', 'b', 'c', 'd'};
	char bloc2[] = { 'a', 'b', 'c', 'd', 'f' };

	int resultat = ft_memcmp(bloc1, bloc2, 5);

	if (resultat == 0) {
		printf("Les deux blocs sont identiques.\n");
	} else if (resultat > 0) {
		printf("Le bloc1 est plus grand que bloc2.\n");
	} else {
		printf("Le bloc1 est plus petit que bloc2.\n");
	}

	return 0;
}
*/