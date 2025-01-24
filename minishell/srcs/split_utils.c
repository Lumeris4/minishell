/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:47:23 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/23 13:58:23 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_special_caractere(char *str, char **split, int j)
{
	if (ft_strncmp(str, "|", 1) == 0)
	{
		split[j] = ft_strdup("|");
		return (1);
	}
	else if (ft_strncmp(str, ">>", 2) == 0)
	{
		split[j] = ft_strdup(">>");
		return (2);
	}
	else if (ft_strncmp(str, "<<", 2) == 0)
	{
		split[j] = ft_strdup("<<");
		return (2);
	}
	else if (ft_strncmp(str, ">", 1) == 0)
	{
		split[j] = ft_strdup(">");
		return (1);
	}
	else
	{
		split[j] = ft_strdup("<");
		return (1);
	}
}

int	ft_double_red(char *s, int i)
{
	int	count;

	count = 0;
	if (ft_strncmp(&s[i], ">>", 2) == 0
		|| ft_strncmp(&s[i], "<<", 2) == 0)
	{
		if (i > 0 && s[i - 1] && !to_ignore(s[i - 1]))
			count++;
		if (s[i + 1] && s[i + 2] && !to_ignore(s[i + 2]))
			count++;
	}
	return (count);
}

int	ft_count_red(char *s, int i)
{
	int	count;

	count = 0;
	if (s[i] && (s[i] == '|' || s[i] == '>' || s[i] == '<'))
	{
		if (i > 0 && s[i - 1] && !to_ignore(s[i - 1]))
			count++;
		if (s[i + 1] && !to_ignore(s[i + 1]))
			count++;
	}
	return (count);
}

int	ft_find_len_in_env(char *s, t_mini *mini)
{
	char	*tmp;
	t_list	*lst;
	int		len;

	lst = mini->env;
	tmp = ft_strdup_dollar(&s[1]);
	if (!tmp)
		return (0);
	len = 0;
	while (lst)
	{
		if (ft_strncmp(tmp, lst->content, ft_strlen(tmp)) == 0
			&& lst->content[ft_strlen(tmp)] == '=')
			break ;
		lst = lst->next;
	}
	if (!lst)
		return (free(tmp), 0);
	len = ft_strlen(lst->content) - ft_strlen(tmp) - 1;
	return (free(tmp), len);
}

void	ft_len_env_var(char *s, t_mini *mini, int *i, int *len)
{
	char	*tmp;

	if (!s[1])
		return ;
	if (s[1] == '?')
	{
		(*i)++;
		tmp = ft_itoa(mini->last_status);
		if (!tmp)
			return ;
		(*len) += ft_strlen(tmp) - 1;
		free(tmp);
	}
	else if (!ft_isalnum(s[1]))
		(*len)++;
	else
	{
		(*i) += ft_count_letters(s);
		(*len) += ft_find_len_in_env(s, mini);
	}
}
