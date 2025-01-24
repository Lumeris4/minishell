/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:29:41 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:29:41 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = (int)ft_strlen(s);
	if (c == '\0')
		return ((char *)&s[i]);
	while (i >= 0)
	{
		i--;
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
	}
	return (NULL);
}
/*
#include <stdio.h>

int main() {
	const char *str = "Bali le petit cheval";
	char *result;

	// Recherche de la dernière occurrence de 'o'
	result = ft_strrchr(str, 'z');

	if (result != NULL)
		printf("Derniere occurrence de 'z' : %s\n", result);
	else
		printf("Caractere non trouve\n");

	return 0;
}
*/