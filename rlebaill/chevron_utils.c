/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:24:29 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/22 18:17:18 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_redirection(char **args, int *i, int number)
{
	int	fd;

	if (!args[*i + 1])
	{
		ft_putstr_fd("Redirection file missing\n", 2);
		return (-1);
	}
	if (number == 1)
		fd = open(args[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(args[*i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Failed to open file\n", 2);
		ft_free_split(args);
		return (-1);
	}
	args[*i] = NULL;
	(*i)++;
	return (fd);
}

static int	handle_redirection(char **args, int *i)
{
	int	fd;

	if (ft_strcmp(args[*i], ">") == 0)
		fd = setup_redirection(args, i, 1);
	else
		fd = setup_redirection(args, i, 2);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	ft_redirection(char **args)
{
	int		save_stdout;
	int		i;

	if (!args || !args[0])
		return (ft_putstr_fd(" no command provided\n", 2), -1);
	save_stdout = dup(STDOUT_FILENO);
	i = -1;
	while (args[++i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0)
			if (handle_redirection(args, &i) == -1)
				return (-1);
	}
	return (save_stdout);
}
