/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:28:52 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:28:52 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static int	add_words(char *result, const char *s, int start, int i)
{
	while (start < i)
		*result++ = s[start++];
	*result = '\0';
	return (1);
}

static int	give_i(int i, char c, char const *s)
{
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		o;
	int		start;

	i = 0;
	o = 0;
	result = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (result == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			i = give_i(i, c, s);
			result[o] = malloc(sizeof(char) * (i - start + 1));
			if (!(result[o]) || (add_words (result[o++], s, start, i) != 1))
				return (NULL);
		}
		else
			i++;
	}
	result[o] = NULL;
	return (result);
}

/*
#include <stdio.h>
int	main(void)
{
	int		i;
	char	**test;

	i = 0;
	test = ft_split("je suis leo", ' ');
	if (test == NULL)
		return (1);
	while (test[i])
	{
		printf("%s\n", test[i]);
		i++;
	}
	// Libérer la mémoire allouée
	i = 0;
	while (test[i])
		free(test[i++]);
	free(test);
	return (0);
}
*/