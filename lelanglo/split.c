/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:35:15 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/14 16:22:59 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i == 0 || (s[i] && s[i + 1]))
	{
		if (((i == 0 && !to_ignore(s[i]) && s[i] != '\0')
				|| (to_ignore(s[i]) && !to_ignore(s[i + 1]))))
			count++;
		if (ft_strncmp(&s[i], ">>", 2) == 0
			|| ft_strncmp(&s[i], "<<", 2) == 0)
		{
			if (s[i - 1] && !to_ignore(s[i - 1]))
				count++;
			if (s[i + 2] && !to_ignore(s[i + 2]))
				count++;
			i++;
		}
		else if (s[i] == '|' || s[i] == '>' || s[i] == '<')
		{
			if (s[i - 1] && !to_ignore(s[i - 1]))
				count++;
			if (s[i + 1] && !to_ignore(s[i + 1]))
				count++;
		}
		if (s[i] == '"' && ++i)
			while (s[i] && s[i] != '"')
				i++;
		else if (s[i] == '\'' && ++i)
			while (s[i] && s[i] != '\'')
				i++;
		i++;
	}
	return (count);
}

static int	ft_len_without_quote(const char *s)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (s[i] && to_ignore(s[i]))
		i++;
	while (s[i] && !to_ignore(s[i]) && s[i] != '|' && s[i] != '>'
		&& s[i] != '<')
	{
		if (s[i] == '"')
		{
			while (s[++i] != '"' && s[i])
				len++;
			len--;
		}
		else if (s[i] == '\'')
		{
			while (s[++i] != '\'' && s[i])
				len++;
			len--;
		}
		len++;
		i++;
	}
	return (len);
}

static int	ft_len_with_quote(const char *s)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (s[i] && to_ignore(s[i]))
		i++;
	while (s[i] && !to_ignore(s[i]) && s[i] != '|' && s[i] != '>'
		&& s[i] != '<')
	{
		if (s[i] == '"')
		{
			len++;
			while (s[++i] != '"' && s[i])
				len++;
		}
		else if (s[i] == '\'')
		{
			len++;
			while (s[++i] != '\'' && s[i])
				len++;
		}
		len++;
		i++;
	}
	return (len - ((s[i] == '|') || s[i] == '>' || s[i] == '<'));
}

static char	*next_word(char const *s)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	word = malloc(sizeof(char) * (ft_len_without_quote(s) + 1));
	if (!word)
		return (NULL);
	while (j < ft_len_without_quote(s))
	{
		if (s[i] == '"')
			while (s[++i] != '"')
				word[j++] = s[i];
		else if (s[i] == '\'')
			while (s[++i] != '\'')
				word[j++] = s[i];
		else
			word[j++] = s[i];
		i++;
	}
	word[j] = '\0';
	return (word);
}

char	**ft_split_quote(char *s)
{
	char	**split;
	int		j;
	int		i;

	split = malloc(sizeof(char *) * (count(s) + 1));
	i = 0;
	j = 0;
	while (i < (int)ft_strlen(s))
	{
		while (s[i] && to_ignore(s[i]))
			i++;
		if (!s[i])
			break ;
		if (ft_strncmp(&s[i], "|", 1) == 0 && ++i)
			split[j] = ft_strdup("|");
		else if (ft_strncmp(&s[i], ">>", 2) == 0 && ++i && ++i)
			split[j] = ft_strdup(">>");
		else if (ft_strncmp(&s[i], "<<", 2) == 0 && ++i && ++i)
			split[j] = ft_strdup("<<");
		else if (ft_strncmp(&s[i], ">", 1) == 0 && ++i)
			split[j] = ft_strdup(">");
		else if (ft_strncmp(&s[i], "<", 1) == 0 && ++i)
			split[j] = ft_strdup("<");
		else
		{
			split[j] = next_word(&s[i]);
			i += ft_len_with_quote(&s[i]) + 1;
		}
		j++;
	}
	split[j] = NULL;
	return (split);
}

// int	main(int ac, char **av)
// {
// 	int		i;
// 	char	**split;

// 	split = ft_split_quote(av[1]);
// 	for (i = 0; split[i]; i++)
// 	{
// 		printf("%s\n", split[i]);
// 		free(split[i]);
// 	}
// 	free(split);
// }
