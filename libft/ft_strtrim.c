/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:29:44 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:29:44 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && in_set(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= start && in_set(s1[end], set))
		end--;
	result = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!result)
		return (NULL);
	ft_strlcpy(result, &s1[start], end - start + 2);
	return (result);
}
/*

#include <stdio.h>
#include "ft_strlcpy.c"
#include "ft_strlen.c"
int     main()
{
	printf("%s\n",ft_strtrim("laboulais","s"));
	return 0;
}
*/