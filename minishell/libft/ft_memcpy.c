/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:28:17 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:28:17 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*str;
	size_t				i;
	unsigned char		*dstr;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (n == 0)
		return (dest);
	i = 0;
	dstr = (unsigned char *)dest;
	str = (const unsigned char *)src;
	while (i < n)
	{
		dstr[i] = str[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int main() {
	char src[] = "Salut!";
	char dest[10];

	ft_memcpy(dest, src, strlen(src) + 1); // On inclut le caractère nul '\0'
	printf("Dest: %s\n", dest);
	
	return 0;
}
*/