/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:26:34 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/06 13:39:20 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *input, char **envp)
{
	char	**split;
	int		i;
	char	path[9] = "/bin/echo";

	split = ft_split(input, ' ');
	if (!split)
		return ;
	if (fork() == 0)
		execve(path, split, envp);
	wait(NULL);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_yes(void)
{
	while (1)
	{
		ft_putchar_fd('y', 1);
		ft_putchar_fd('\n', 1);
	}
}
