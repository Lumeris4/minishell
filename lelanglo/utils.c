/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:45:21 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/20 18:41:36 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	to_ignore(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_strindex(const char *str, const char *substr)
{
	int	i;
	int	j;

	if (!str || !substr)
		return (-1);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (substr[j] && str[i + j] == substr[j])
			j++;
		if (!substr[j])
			return (i);
		i++;
	}
	return (-1);
}

