/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:24:29 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/24 10:49:24 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_redirection(char **args, int *i, int is_append)
{
	int	fd;

	if (!args[*i + 1])
	{
		ft_putstr_fd(" redirection file missing\n", 2);
		return (-1);
	}
	if (is_append)
		fd = open(args[*i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(args[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(" failed to open file\n", 2);
		return (-1);
	}
	return (fd);
}

static int	handle_redirection(char **args, int *i)
{
	int	fd;
	int	is_append;

	is_append = (ft_strcmp(args[*i], ">>") == 0);
	fd = setup_redirection(args, i, is_append);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	*i += 2;
	return (0);
}

int	ft_redirection(char **args)
{
	int	save_stdout;
	int	i;

	if (!args || !args[0])
		return (ft_putstr_fd(" no command provided\n", 2), -1);
	save_stdout = dup(STDOUT_FILENO);
	if (save_stdout == -1)
		return (ft_putstr_fd(" dup failed\n", 2), -1);
	i = 0;
	while (args[i])
	{
		if (args[i] && (ft_strcmp(args[i], ">") == 0
				|| ft_strcmp(args[i], ">>") == 0))
		{
			if (handle_redirection(args, &i) == -1)
			{
				dup2(save_stdout, STDOUT_FILENO);
				close(save_stdout);
				return (-1);
			}
		}
		else
			i++;
	}
	return (save_stdout);
}

void	ft_test_signal(int *signal, t_mini *mini)
{
	if (*signal == 130)
	{
		mini->last_status = 130;
		*signal = 0;
	}
}
