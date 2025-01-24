/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:32:30 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/24 11:44:16 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_splited_split(char ***splited_split)
{
	int	i;

	i = 0;
	while (splited_split[i])
	{
		ft_free_split(splited_split[i]);
		i++;
	}
	free(splited_split);
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

void	ft_free_all(t_mini *mini, char ***splited_split,
	char **split, char *path)
{
	if (splited_split)
		ft_free_splited_split(splited_split);
	if (split)
		ft_free_split(split);
	if (mini->input)
		free(mini->input);
	if (mini->env)
		ft_lstclear(&mini->env, free);
	if (mini->export)
		ft_lstclear(&mini->export, free);
	if (path)
		free(path);
}
