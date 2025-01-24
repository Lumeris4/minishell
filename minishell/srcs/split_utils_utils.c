/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:32:09 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/17 12:32:33 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_letters(char *s)
{
	int	len;

	len = 1;
	while (s[len] && ft_isalnum(s[len]))
		len++;
	return (len - 1);
}

char	*ft_strdup_dollar(char *s)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	while (s[len] && ft_isalnum(s[len]))
		len++;
	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_copy_env_var(char *str, char *split, t_mini *mini)
{
	t_list	*lst;
	char	*tmp;
	int		i;
	int		j;

	tmp = ft_strdup_dollar(&split[1]);
	lst = mini->env;
	while (lst)
	{
		if (ft_strncmp(tmp, lst->content, ft_strlen(tmp)) == 0
			&& lst->content[ft_strlen(tmp)] == '=')
			break ;
		lst = lst->next;
	}
	if (!lst)
		return (free(tmp), 0);
	i = ft_strlen(tmp);
	j = -1;
	while (lst->content[++i])
		str[++j] = lst->content[i];
	return (free(tmp), j + 1);
}

int	ft_put_env_var(char *s, char *word, t_mini *mini, int *i)
{
	char	*tmp;
	int		j;
	int		len;

	j = -1;
	if (!s[1])
		return (0);
	if (s[1] == '?')
	{
		(*i)++;
		tmp = ft_itoa(mini->last_status);
		if (!tmp)
			return (0);
		while (tmp[++j])
			word[j] = tmp[j];
		len = ft_strlen(tmp);
		return (free(tmp), len);
	}
	else if (!ft_isalnum(s[1]))
		return (0);
	else
	{
		(*i) += ft_count_letters(s);
		return (ft_copy_env_var(word, s, mini));
	}
}

int	ft_fill_word(char *word, char *s, t_mini *mini, int *i)
{
	int	j;

	j = 0;
	if (s[*i] == '$' && s[(*i) + 1]
		&& (ft_isalnum(s[(*i) + 1]) || s[(*i) + 1] == '?'))
		j += ft_put_env_var(&s[*i], &word[j], mini, i);
	else
		word[j++] = s[*i];
	return (j);
}
