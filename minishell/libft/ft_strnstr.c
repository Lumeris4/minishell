/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:29:35 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:29:35 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (i != len && haystack[i] != '\0')
	{
		j = 0;
		while ((haystack[i + j] == needle[j]) && ((i + j) < len))
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int main() {
	const char *haystack = "Hello, world!";
	const char *needle = "world";
	char *result;

	result = ft_strnstr(haystack, needle, 4);

	if (result != NULL)
		printf("Sous-chaine trouvee : %s\n", result);
	else
		printf("Sous-chaine non trouvee\n");

	return 0;
}
*/