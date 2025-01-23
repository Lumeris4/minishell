/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:54:30 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/21 11:51:22 by rlebaill         ###   ########.fr       */
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

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	to_ignore(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	show_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_putstr_fd("-> ", 2);
		ft_putstr_fd(split[i], 2);
		ft_putstr_fd("\n", 2);
		i++;
	}
}

// void	show_splited_split(char ***splited_split)
// {
// 	int	i;

// 	i = 0;
// 	printf(">--------<\n");
// 	while (splited_split[i])
// 	{
// 		show_split(splited_split[i]);
// 		printf("----------\n");
// 		i++;
// 	}
// }
