/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:35:15 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/07 13:11:20 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c
				|| s[i - 1] == '"' || s[i - 1] == '\''))
			count++;
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
		}
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
	if (s[i] == '"')
	{
		i++;
		while (s[i] && s[i] != '"')
			i++;
	}
	else if (s[i] == '\'')
	{
		i++;
		while (s[i] && s[i] != '\'')
			i++;
	}
	else
	{
		while (s[i] && s[i] != c && s[i] != '"' && s[i] != '\'')
			i++;
	}
	return (i);
}

char	**ft_split_quote(char *s)
{
	char	**result;
	int		i;
	int		o;
	int		start;

	i = 0;
	o = 0;
	result = malloc(sizeof(char *) * (ft_count(s, ' ') + 1));
	if (result == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] != ' ')
		{
			start = i;
			i = give_i(i, ' ', s);
			if (s[i] == '"' || s[i] == '\'')
				start++;
			result[o] = malloc(sizeof(char) * (i - start + 1));
			if (!(result[o]) || (add_words (result[o++], s, start, i) != 1))
				return (NULL);
		}
		if (s[i] == ' ' || s[i] == '"' || s[i] == '\'')
			i++;
	}
	result[o] = NULL;
	return (result);
}
