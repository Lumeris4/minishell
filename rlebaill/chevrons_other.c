/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevrons_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:21:04 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/22 18:13:40 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_input_redirection(char **args, int *i)
{
	int	fd;

	if (!args[*i + 1])
	{
		perror("Redirection file missing");
		ft_free_split(args);
		return (-1);
	}
	fd = open(args[*i + 1], O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open file for input redirection");
		return (-1);
	}
	args[*i] = NULL;
	(*i)++;
	return (fd);
}

int	ft_other_redirection(char *input, t_mini *mini)
{
	int		fd;
	int		save_stdin;
	char	**args;
	int		i;

	args = ft_split_quote(input, mini);
	if (!args || !args[0])
		return (perror(" no command provided"), ft_free_split(args), -1);
	save_stdin = dup(STDIN_FILENO);
	if (save_stdin == -1)
		return (perror(" dup fail"), ft_free_split(args), -1);
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<") == 0)
		{
			fd = setup_input_redirection(args, &i);
			if (dup2(fd, STDIN_FILENO) == -1)
				return (close(fd), ft_free_split(args), -1);
			close(fd);
		}
		else
			i++;
	}
	return (ft_free_split(args), save_stdin);
}
