/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:54:30 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/24 11:32:54 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_get_size_mat(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	to_ignore(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	have_right(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (ft_strcmp(split[i], ">") == 0
			|| ft_strcmp(split[i], ">>") == 0)
			return (1);
		i++;
	}
	return (0);
}
