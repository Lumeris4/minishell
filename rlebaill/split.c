/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:35:15 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/20 16:08:29 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i == 0 || (s[i] && s[i + 1]))
	{
		if (((s[i] && i == 0 && !to_ignore(s[i]))
				|| (to_ignore(s[i]) && !to_ignore(s[i + 1]))))
			count++;
		if (ft_strncmp(&s[i], ">>", 2) == 0
			|| ft_strncmp(&s[i], "<<", 2) == 0)
			count += ft_dubble_red(s, i++);
		else
			count += ft_count_red(s, i);
		if (s[i] && s[i] == '"' && ++i)
			while (s[i] && s[i] != '"')
				i++;
		else if (s[i] && s[i] == '\'' && ++i)
			while (s[i] && s[i] != '\'')
				i++;
		i++;
	}
	return (count);
}

static int	ft_len_without_quote(char *s, int i, t_mini *mini, int len)
{
	while (s[i] && to_ignore(s[i]))
		i++;
	while (s[i] && !to_ignore(s[i]) && s[i] != '|' && s[i] != '>'
		&& s[i] != '<')
	{
		if (s[i] && s[i] == '$')
			ft_len_env_var(&s[i], mini, &i, &len);
		else if (s[i] && s[i] == '"')
		{
			while (s[++i] && s[i] != '"')
			{
				if (s[i] && s[i] == '$')
					ft_len_env_var(&s[i], mini, &i, &len);
				len++;
			}
			len--;
		}
		else if (s[i] && s[i] == '\'' && len-- + 1)
			while (s[++i] != '\'' && s[i])
				len++;
		len++;
		i++;
	}
	return (len);
}

static int	ft_len_with_quote(char *s, int i)
{
	int	len;

	len = 0;
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

static char	*next_word(char *s, t_mini *mini, int i, int j)
{
	char	*word;

	word = malloc(sizeof(char) * (ft_len_without_quote(s, 0, mini, 0) + 1));
	if (!word)
		return (NULL);
	while (j < ft_len_without_quote(s, 0, mini, 0) && ++i + 1)
	{
		if (s[i] == '$' && s[i + 1]
			&& (ft_isalnum(s[i + 1]) || s[i + 1] == '?'))
			j += ft_put_env_var(&s[i], &word[j], mini, &i);
		else if (s[i] == '"')
			while (s[++i] != '"')
				j += ft_fill_word(&word[j], s, mini, &i);
		else if (s[i] == '\'')
			while (s[++i] != '\'')
				word[j++] = s[i];
		else
			word[j++] = s[i];
	}
	return (word[j] = '\0', word);
}

char	**ft_split_quote(char *s, t_mini *mini)
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
		if (s[i] == '|' || s[i] == '<' || s[i] == '>')
			i += ft_special_caractere(&s[i], split, j);
		else
		{
			split[j] = next_word(&s[i], mini, -1, 0);
			i += ft_len_with_quote(&s[i], 0) + 1;
		}
		j++;
	}
	split[j] = NULL;
	return (split);
}
