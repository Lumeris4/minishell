/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:28:22 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:28:22 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	for_the_norm(unsigned char *dstr, size_t n
						, const unsigned char *str)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dstr[i] = str[i];
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dstr;
	const unsigned char	*str;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (n == 0)
		return (dest);
	dstr = (unsigned char *)dest;
	str = (const unsigned char *)src;
	if (dstr > str)
	{
		while (n > 0)
		{
			n--;
			dstr[n] = str[n];
		}
	}
	else
		for_the_norm(dstr, n, str);
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "Hello, World!";
	char str2[] = "Hello, World!";

	ft_memmove(str + 6, str, 6);  // Déplacer "Hello," à la fin de "World!"
	memmove(str2 + 6, str2, 6);
	printf("Result: %s\n", str);
	printf("Result: %s\n", str2);
	return 0;
}
*/
